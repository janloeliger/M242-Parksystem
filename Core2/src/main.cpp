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

byte triggerPin = 13;
byte echoPin = 14;

unsigned long previousCheckTime = 0;
u_int8_t reservedParkCount;

void setup() {
  M5.begin();
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop() {
  unsigned long currentMillis = millis();

  // Checking Task
  if (currentMillis - previousCheckTime >= CHECK_INTERVAL) {
    previousCheckTime = currentMillis;
    double* distances = HCSR04.measureDistanceCm();
    bool isLeftParked = isParked(distances[0]);

    // Drawing Task
    drawDisplay(isLeftParked, 0);
  }


}

void drawDisplay(int leftFreeParkingCount, int rightFreeParkingCount) {
  // left parking spot
  M5.Lcd.setCursor(PADDING, FONT_SIZE);
  M5.Lcd.setTextSize(FONT_SIZE);
  M5.Lcd.print(leftFreeParkingCount);
  M5.Lcd.setCursor(FONT_SIZE, FONT_SIZE * 4);
  M5.Lcd.print("<--");
  
  // right parking spot
  M5.Lcd.setCursor(SCREEN_WIDTH - PADDING - FONT_SIZE, SCREEN_HEIGHT - PADDING - FONT_SIZE * 4);
  M5.Lcd.setTextSize(FONT_SIZE);
  M5.Lcd.print(rightFreeParkingCount);
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