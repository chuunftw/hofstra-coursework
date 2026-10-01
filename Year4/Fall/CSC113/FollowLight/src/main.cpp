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
    for (int i = 0; i < (int)input.length(); i++) {
      if (input[i] < '0' || input[i] > '9') {
        valid = false;
      }
    }

    long value = 0;

    if (valid) {
      value = input.toInt();
    }

    // If the number is within the allowed range, display it and return it.
    // Returning ends this function and supplies the number to its caller.
    if (value >= 1 && value <= maximum) {
      Serial.print("Selected: ");
      Serial.println(value);
      return (int)value;
    }
    // Otherwise, display the allowed range before the loop asks again.
    Serial.print("Enter a whole number from 1 to ");
    Serial.println(maximum);
  }
}

int scan() {
  int maxPos = 0;
  int maxVal = -1;

  // Announce the scan, turn on the LED, and allow the servo to reach zero.
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

    // Update the best reading and angle if this return sweep finds brighter light.
    if (currentVal > maxVal) {
      maxVal = currentVal;
      maxPos = pos;
    }
  }

  Serial.print("Scan finished. Highest light reading: ");
  Serial.println(maxVal);
  return maxPos;
}

void goToLight(int maxPos) {
  Serial.print("Moving to brightest position: ");
  Serial.print(maxPos);
  Serial.println(" degrees.");

  // Turn off the scanning LED, move to the selected angle, and allow time to arrive.
  digitalWrite(lightPin, LOW);
  myservo.write(maxPos);
  delay(500);
}

void userDelay() {
  int previousButtonState = digitalRead(buttonPin);
  int referenceLight = analogRead(lightReaderPin);

  // Display the current light reading and explain when another scan will start.
  Serial.print("Light reading at this position: ");
  Serial.println(referenceLight);
  Serial.print("Waiting up to ");
  Serial.print(timer);
  Serial.println(" seconds, or until a button press or light change.");

  for (int i = 0; i < timer * 10; i++) {
    // INPUT_PULLUP gives HIGH when released and LOW when pressed.
    // Detect a new press and wait briefly to reduce the effect of button bounce.
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && previousButtonState == HIGH) {
      delay(20);

      // If the button is still pressed, end this function to begin another scan.
      if (digitalRead(buttonPin) == LOW) {
        Serial.println("Button pressed. Rescanning.");
        return;
      }
    }

    // Remember the button state for the next check and take a new light reading.
    previousButtonState = buttonState;
    int currentLight = analogRead(lightReaderPin);
    // abs() measures the size of either an increase or a decrease in light.
    // End the wait if this change reaches the user's sensitivity threshold.
    if (abs(currentLight - referenceLight) >= sensitivity) {
      Serial.println("Light level changed. Rescanning.");
      return;
    }

    delay(100);
  }

  // Reaching the end of the wait lets loop() start another scan.
  Serial.println("Timer finished. Rescanning.");
}

void setup() {
  // Start Serial communication, configure the LED, and enable the button's pull-up.
  Serial.begin(9600);
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach the servo signal to its pin and move the arm to its starting position.
  myservo.attach(servoPin);
  myservo.write(0);
  delay(500);
  timer = readSetting("Seconds to wait after each scan (1-100):", 100);
  sensitivity = readSetting("Light-change threshold (1-1000; lower is more sensitive):", 1000);
}

// Repeatedly scan, move to the brightest position, and wait for a rescan.
void loop() {
  // Find the brightest angle, move there, then wait until a rescan is triggered.
  int maxPos = scan();
  goToLight(maxPos);
  userDelay();
}
