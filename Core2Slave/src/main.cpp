#include <M5Core2.h>
#include <Arduino.h>
#include <HCSR04.h>
#include <Wire.h>

// Functions
void requestDistance();

// constants
const int ARDUINO_ADDRESS = 2;

// Pins
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 14;


void setup() {
  //inits m5
    M5.begin();
    M5.Lcd.clear();
  // inits i2c
  Wire.begin(ARDUINO_ADDRESS);
  Wire.onRequest(requestDistance);
  Serial.begin(9600);
  // inits hcsr04
  HCSR04.begin(TRIGGER_PIN, ECHO_PIN);
}

void loop() {}

void requestDistance() {
  double *distances = HCSR04.measureDistanceCm();
  int intDistance = (int) distances[0];
  Wire.write(intDistance);
}