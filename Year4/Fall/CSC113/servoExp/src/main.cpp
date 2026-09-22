#include <Arduino.h>
#include <Servo.h>

Servo servoMotor;
int servoPin = 9;

void setup() {
  servoMotor.attach(servoPin);
  servoMotor.write(0);
  delay(1000);
}

void loop() {
  servoMotor.write(180);
  delay(1000);

  servoMotor.write(0);
  delay(1000);
}
