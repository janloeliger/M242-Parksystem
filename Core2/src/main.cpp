#include <Arduino.h>
#include "HCSR04.h"

float getDistance();

UltraSonicDistanceSensor distanceSensor(33, 32);  // Initialize sensor that uses digital pins 13 and 12.

void setup() {
  Serial.begin(9600);
}

void loop() {

getDistance();
}

float getDistance() {
  double distance = distanceSensor.measureDistanceCm();

  Serial.print(F("°C - Distance: "));
  Serial.print(distance);
  Serial.println(F("cm"));
  delay(1000);
  return 0;
}