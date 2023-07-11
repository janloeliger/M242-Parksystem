#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <TM1637Display.h>

// Functions
void checkGateStatus();
void receiveData(int byteCount);
void writeDisplay(int n);

// constants
const int SERVO_MAX_POS = 120;
const int SERVO_MIN_POS = 45;
const int MASTER_ADDRESS = 1;
const int ARDUINO_ADDRESS = 3;
const int CHECK_INTERVAL = 5000;

// Pins
const int SERVO_ENTRY_PIN = 11;
const int SERVO_EXIT_PIN = 10;
const int BUTTON_ENTRY_PIN = 9;
const int BUTTON_EXIT_PIN = 8;
const int DISPLAY_CLK_PIN = 7;
const int DISPLAY_DIO_PIN = 6;

Servo servoEntry;
Servo servoExit;
TM1637Display display(DISPLAY_CLK_PIN, DISPLAY_DIO_PIN);

unsigned long entryCheckTime = 0;
bool entryIsOpen = false;
unsigned long exitCheckTime = 0;
bool exitIsOpen = false;

void setup() {
  // init display
  display.setBrightness(0x0f);
  writeDisplay(0);
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
  Wire.onReceive(receiveData);
  Serial.begin(9600);
}

void loop() {
  checkGateStatus();
}

void checkGateStatus() {
  unsigned long currentMillis = millis();
  // checks entry gate
  if (digitalRead(BUTTON_ENTRY_PIN) == LOW && entryIsOpen == false) {
    servoEntry.write(SERVO_MAX_POS);
    entryCheckTime = currentMillis;
    entryIsOpen = true;
  } else if (currentMillis - entryCheckTime >= CHECK_INTERVAL && entryIsOpen == true) {
    servoEntry.write(SERVO_MIN_POS);
    entryIsOpen = false;
  }

  // checks exit gate
    if (digitalRead(BUTTON_EXIT_PIN) == LOW && exitIsOpen == false) {
    servoExit.write(SERVO_MAX_POS);
    exitCheckTime = currentMillis;
    exitIsOpen = true;
  } else if (currentMillis - exitCheckTime >= CHECK_INTERVAL && exitIsOpen == true) {
    servoExit.write(SERVO_MIN_POS);
    exitIsOpen = false;
  }
}

void receiveData(int byteCount) {
  if (Wire.available() >= sizeof(int)) {
    int parkingCount = Wire.read();
    writeDisplay(parkingCount);
  }
}

void writeDisplay(int n) {
  display.showNumberDec(n, false);
}
