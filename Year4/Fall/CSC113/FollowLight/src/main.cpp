#include <Arduino.h>
#include <Servo.h>

const int buttonPin = 4;
const int lightPin = 7;
const int lightReaderPin = A1;
const int servoPin = 2;

Servo myservo;
int timer;
int sensitivity;
// Ask for a whole number through Serial and check that it is in range.
int readSetting(const char *prompt, int maximum) {
  Serial.println(prompt);

  while (true) {
    if (Serial.available() == 0) {
      delay(10);
      continue;
    }

    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) {
      continue;
    }

    bool valid = input.length() <= 4; 
    for (unsigned int i = 0; i < input.length(); i++) {
      if (input[i] < '0' || input[i] > '9') {
        valid = false;
      }
    }

    long value = 0;

    if (valid) {
      value = input.toInt();
    }

    if (value >= 1 && value <= maximum) {
      Serial.print("Selected: ");
      Serial.println(value);
      return (int)value;
    }
    Serial.print("Enter a whole number from 1 to ");
    Serial.println(maximum);
  }
}
// Scan in both directions and return the angle with the highest light reading.
int scan() {
  int maxPos = 0;
  int maxVal = -1;

  Serial.println("Scan started.");
  digitalWrite(lightPin, HIGH);
  myservo.write(0);
  delay(500);

  for (int pos = 0; pos <= 180; pos++) {
    myservo.write(pos);
    delay(30);
    int currentVal = analogRead(lightReaderPin);

    if (currentVal > maxVal) {
      maxVal = currentVal;
      maxPos = pos;
    }
  }

  for (int pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
    delay(30);
    int currentVal = analogRead(lightReaderPin);

    if (currentVal > maxVal) {
      maxVal = currentVal;
      maxPos = pos;
    }
  }

  Serial.print("Scan finished. Highest light reading: ");
  Serial.println(maxVal);
  return maxPos;
}
// Move the arm to the brightest position found during the scan.
void goToLight(int maxPos) {
  Serial.print("Moving to brightest position: ");
  Serial.print(maxPos);
  Serial.println(" degrees.");

  digitalWrite(lightPin, LOW);
  myservo.write(maxPos);
  delay(500);
}
// Wait for the timer, a button press, or a change in light level.
void userDelay() {
  int previousButtonState = digitalRead(buttonPin);
  int referenceLight = analogRead(lightReaderPin);
  unsigned long startTime = millis();

  Serial.print("Light reading at this position: ");
  Serial.println(referenceLight);
  Serial.print("Waiting up to ");
  Serial.print(timer);
  Serial.println(" seconds, or until a button press or light change.");

  while (millis() - startTime < timer * 1000UL) {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && previousButtonState == HIGH) {
      delay(20);

      if (digitalRead(buttonPin) == LOW) {
        Serial.println("Button pressed. Rescanning.");
        return;
      }
    }

    previousButtonState = buttonState;
    int currentLight = analogRead(lightReaderPin);
    if (abs(currentLight - referenceLight) >= sensitivity) {
      Serial.println("Light level changed. Rescanning.");
      return;
    }

    delay(100);
  }

  Serial.println("Timer finished. Rescanning.");
}

// Set up the pins and servo, then ask for the scan interval and sensitivity.
void setup() {
  Serial.begin(9600);
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);
  pinMode(buttonPin, INPUT_PULLUP);

  myservo.attach(servoPin);
  myservo.write(0);
  delay(500);
  timer = readSetting("Seconds to wait after each scan (1-100):", 100);
  sensitivity = readSetting("Light-change threshold (1-1000; lower is more sensitive):", 1000);
}

// Repeatedly scan, move to the brightest position, and wait for a rescan.
void loop() {
  int maxPos = scan();
  goToLight(maxPos);
  userDelay();
}
