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
  pinMode(pirPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), handleInterrupt, CHANGE);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (motionDetected) {
    motionDetected = false;  // Acknowledge and reset flag
    // Execute your heavy or blocking logic completely safely here inside the loop
    pirValue = digitalRead(pirPin);
    digitalWrite(ledPin, pirValue);
    if (pirValue == HIGH) {
      Serial.println("Motion detected.");
    } else {
      Serial.println("Motion ended.");
    }
  }
}
