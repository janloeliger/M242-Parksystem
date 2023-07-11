#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

// Functions
void checkGateStatus();

// constants
const int SERVO_MAX_POS = 120;
const int SERVO_MIN_POS = 45;
const int MASTER_ADDRESS = 1;
const int ARDUINO_ADDRESS = 3;
const int CHECK_INTERVAL = 5000;

// Pins
const int SERVO_ENTRY_PIN = 11;
const int SERVO_EXIT_PIN = 10;
const int BUTTON_ENTRY_PIN = 6;
const int BUTTON_EXIT_PIN = 8;
const int SDA_PIN = 19;
const int SCL_PIN = 18;

Servo servoEntry; 
Servo servoExit;

unsigned long entryCheckTime = 0;
bool entryIsOpen = false;
unsigned long exitCheckTime = 0;
bool exitIsOpen = false;

void setup() {
  // inits servos
  servoEntry.attach(SERVO_ENTRY_PIN);
  servoExit.attach(SERVO_EXIT_PIN);
  //servoEntry.write(SERVO_MIN_POS);
  servoExit.write(SERVO_MIN_POS);
  // sets buttons
  pinMode(BUTTON_ENTRY_PIN, INPUT);
  pinMode(BUTTON_EXIT_PIN, INPUT);
  // inits i2c
  Wire.begin(ARDUINO_ADDRESS);
  //Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
}

void loop() {
  checkGateStatus();
}

void checkGateStatus() {
  unsigned long currentMillis = millis();
  
  if (digitalRead(BUTTON_ENTRY_PIN) == LOW && exitIsOpen == false) {
    servoEntry.write(SERVO_MAX_POS);
    entryCheckTime = currentMillis;
    exitIsOpen = true;
  } else if (currentMillis - entryCheckTime >= CHECK_INTERVAL && exitIsOpen == true) {
    servoEntry.write(SERVO_MIN_POS);
    exitIsOpen = false;
    Serial.println(entryCheckTime);
  }
}