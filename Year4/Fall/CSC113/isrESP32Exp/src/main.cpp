#include <Arduino.h>

int ledPin = 2; // LED on Pin 13 of Arduino
int pirPin = 18; // Input for HC-S501
int pirValue; // Place to store read PIR Value
volatile bool motionDetected = false;

void IRAM_ATTR handleInterrupt() {
  motionDetected = true;
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
  pinMode(pirPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pirPin), handleInterrupt, FALLING);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (motionDetected) {
    motionDetected = false;  // Acknowledge and reset flag
    // Execute your heavy or blocking logic completely safely here inside the loop
    Serial.println("Motion detected.");
    pirValue = digitalRead(pirPin);
    digitalWrite(ledPin, pirValue);
  }
}