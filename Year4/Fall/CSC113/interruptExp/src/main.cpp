#include <Arduino.h>

const byte ledPin = 3;
const byte inputPin = 2;
volatile bool ledState = LOW;

void toggleLed() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);

  digitalWrite(ledPin, ledState);
  attachInterrupt(digitalPinToInterrupt(inputPin), toggleLed, FALLING);
}

void loop() {
  // Main loop intentionally left empty.
  // The interrupt toggles the LED whenever the input signal falls.
}

