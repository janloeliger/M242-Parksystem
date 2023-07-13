#include <M5Core2.h>
#include <Arduino.h>
#include <HCSR04.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>

// functions
void drawDisplay(int, int);
bool isParked(int);
void connectToMqtt();
void connectToWifi();

// constants
const int FONT_SIZE = 20;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const int PADDING = 80;
const int CHECK_INTERVAL = 500; // Interval for checking task in milliseconds
const int ARDUINO_MONITOR_ADDRESS = 3;
const int M5CORE2_DISTANCE_ADDRESS = 2;
const int PARKING_COUNT = 2;
const char* SSID = "Moin (2)";
const char* WIFI_PASSWORD = "passwort";
const char* MQTT_SERVER = "cloud.tbz.ch";
const int MQTT_PORT = 1883;

// Pins
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 14;

unsigned long previousCheckTime = 0;
int reservedParkCount = 0;

WiFiClient net;
MQTTClient client;

void setup()
{
  // M5 init
  M5.begin();
  Wire.begin();
  Serial.begin(9600);

  // Sensors
  HCSR04.begin(TRIGGER_PIN, ECHO_PIN);

  // sets the i2c display at starup
  Wire.beginTransmission(ARDUINO_MONITOR_ADDRESS);
  Wire.write(highByte(0));
  Wire.write(lowByte(PARKING_COUNT));
  Wire.endTransmission();

  // Wifi & MQTT
  WiFi.begin(SSID, WIFI_PASSWORD);
  client.begin(MQTT_SERVER, MQTT_PORT, net);
  connectToWifi();
  connectToMqtt();
}

void loop()
{
  // checks if MQTT is connected
    if (!client.connected()) {
    connectToMqtt();
  }
  
  unsigned long currentMillis = millis();
  int oldParkedCount = reservedParkCount;

  // Checking Task
  if (currentMillis - previousCheckTime >= CHECK_INTERVAL)
  {
    previousCheckTime = currentMillis;

    // measures with the I2C sensor
    bool isRightParked = 0;
    /*Wire.requestFrom(2, 1);
    while (Wire.available())
    {                      // peripheral may send less than requested
      isRightParked = isParked(Wire.read()); // receive a byte as character
    }*/
    // measures with the attached sensor
    double *distances = HCSR04.measureDistanceCm();
    bool isLeftParked = isParked(distances[0]);
    // sets the parked car count
    reservedParkCount = isLeftParked + isRightParked;
    // Drawing Task
    drawDisplay(isLeftParked, isRightParked);
  }

  if (reservedParkCount != oldParkedCount)
  {
    Serial.println("send data");
    Wire.beginTransmission(ARDUINO_MONITOR_ADDRESS);
    Wire.write(highByte(0));
    Wire.write(lowByte(PARKING_COUNT - reservedParkCount));
    Wire.endTransmission();
  }
}

void drawDisplay(int leftFreeParkingCount, int rightFreeParkingCount)
{
  // left parking spot
  M5.Lcd.setCursor(PADDING, FONT_SIZE);
  M5.Lcd.setTextSize(FONT_SIZE);
  M5.Lcd.print(1 - leftFreeParkingCount);
  M5.Lcd.setCursor(FONT_SIZE, FONT_SIZE * 4);
  M5.Lcd.print("<--");

  // right parking spot
  M5.Lcd.setCursor(SCREEN_WIDTH - PADDING - FONT_SIZE, SCREEN_HEIGHT - PADDING - FONT_SIZE * 4);
  M5.Lcd.setTextSize(FONT_SIZE);
  M5.Lcd.print(1 - rightFreeParkingCount);
  M5.Lcd.setCursor(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PADDING - FONT_SIZE);
  M5.Lcd.print("-->");
}

bool isParked(int distance)
{
  if (distance <= 8)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void connectToWifi() {
  Serial.print("Checking WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
}

void connectToMqtt() {
  Serial.print("\nConnecting to MQTT broker...");
  while (!client.connect("core2", "core2J", "")) {

    Serial.print(".");

    delay(1000);

  }
  client.subscribe("/parking");
}