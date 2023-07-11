#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

// constants
const int SERVO_MAX_POS = 120;
const int SERVO_MIN_POS = 45;
const int MASTER_ADDRESS = 1;
const int ARDUINO_ADDRESS = 3;

// Pins
const int SERVO_ENTRY_PIN = 11;
const int SERVO_EXIT_PIN = 10;
const int BUTTON_ENTRY_PIN = 9;
const int BUTTON_EXIT_PIN = 8;
const int SDA_PIN = 19;
const int SCL_PIN = 18;

Servo servoEntry; 
Servo servoExit;

void setup() {
  // inits servos
  servoEntry.attach(SERVO_ENTRY_PIN);
  servoExit.attach(SERVO_EXIT_PIN);
  servoEntry.write(SERVO_MIN_POS);
  servoExit.write(SERVO_MIN_POS);
  // sets buttons
  pinMode(BUTTON_ENTRY_PIN, INPUT);
  pinMode(BUTTON_EXIT_PIN, INPUT);
  // inits i2c
  Wire.begin(ARDUINO_ADDRESS);
  Wire.onReceive(receiveEvent); 
}

void loop() {
  if(digitalRead(BUTTON_ENTRY_PIN) == 1) {
    servoEntry.write(SERVO_MAX_POS);
    delay(200);
    servoEntry.write(SERVO_MIN_POS);
  }

    if(digitalRead(BUTTON_EXIT_PIN) == 1) {
    servoExit.write(SERVO_MAX_POS);
    delay(200);
    servoExit.write(SERVO_MIN_POS);
  }

}

void receiveEvent(int numBytes) {
  while (Wire.available()) {
    int parkingCount = Wire.read();
    
}