#include <M5Core2.h>
#include <Arduino.h>
#include <HCSR04.h>

// functions
void drawDisplay(int, int);
bool isParked(int);

// constants
const int FONT_SIZE = 20;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const int PADDING = 80;
const int CHECK_INTERVAL = 500;  // Interval for checking task in milliseconds
const int ARDUINO_MONITOR_ADDRESS = 3;
const int PARKING_COUNT = 2;

byte triggerPin = 13;
byte echoPin = 14;

unsigned long previousCheckTime = 0;
u_int8_t reservedParkCount;

void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop() {
  unsigned long currentMillis = millis();
  int oldParkedCount = reservedParkCount;

  // Checking Task
  if (currentMillis - previousCheckTime >= CHECK_INTERVAL) {
    previousCheckTime = currentMillis;
    double* distances = HCSR04.measureDistanceCm();
    bool isLeftParked = isParked(distances[0]);
    // sets the parked car count
    reservedParkCount = isLeftParked + 0;
    // Drawing Task
    drawDisplay(isLeftParked, 0);
  }
  
  if(reservedParkCount != oldParkedCount) {
    Serial.println("send data");
    Wire.beginTransmission(ARDUINO_MONITOR_ADDRESS);
    Wire.write(reservedParkCount);
    Wire.endTransmission();
  }
}

void drawDisplay(int leftFreeParkingCount, int rightFreeParkingCount) {
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

bool isParked(int distance) {
  if(distance <= 8) {
    return true;
  } else {
    return false;
  }
}