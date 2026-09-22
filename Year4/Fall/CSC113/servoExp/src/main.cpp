#include <Arduino.h>
#include <Servo.h>

Servo servoMotor;
int servoPin = 9;

void setup() {
  servoMotor.attach(servoPin);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    servoMotor.write(angle);
    delay(200);
  }

  for (int angle = 179; angle >= 1; angle--) {
    servoMotor.write(angle);
    delay(200);
  }
}

