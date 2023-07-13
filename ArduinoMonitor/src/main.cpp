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
const int SERVO_SPECIAL_MAX_POS = 90;
const int SERVO_SPECIAL_MIN_POS = 10;
const int MASTER_ADDRESS = 1;
const int ARDUINO_ADDRESS = 3;
const int SERVO_INTERVAL = 10000;

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
  servoEntry.write(SERVO_MIN_POS);
  servoExit.write(SERVO_SPECIAL_MIN_POS);
  // sets buttons
  pinMode(BUTTON_ENTRY_PIN, INPUT_PULLUP);
  pinMode(BUTTON_EXIT_PIN, INPUT_PULLUP);
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
    Serial.println("Gate is open, entry");
    servoEntry.write(SERVO_MIN_POS);
    entryCheckTime = currentMillis;
    entryIsOpen = true;
  } 
  if (currentMillis - entryCheckTime >= SERVO_INTERVAL && entryIsOpen == true) {
    Serial.println("Gate is clsoed, entry");
    servoEntry.write(SERVO_MAX_POS);
    entryIsOpen = false;
  }

  // checks exit gate
  if (digitalRead(BUTTON_EXIT_PIN) == LOW && exitIsOpen == false) {
    Serial.println("Gate is open, exit");
    servoExit.write(SERVO_SPECIAL_MAX_POS);
    exitCheckTime = currentMillis;
    exitIsOpen = true;
  } 
  if (currentMillis - exitCheckTime >= SERVO_INTERVAL && exitIsOpen == true) {
    Serial.println("Gate is clsoed, exit");
    servoExit.write(SERVO_SPECIAL_MIN_POS);
    exitIsOpen = false;
  }
}

void receiveData(int byteCount) {
  Serial.print("receives data");
  if (Wire.read() == 0) {
    int parkingCount = Wire.read();
    writeDisplay(parkingCount);
  }
}

void writeDisplay(int n) {
  display.showNumberDec(n, false);
}
