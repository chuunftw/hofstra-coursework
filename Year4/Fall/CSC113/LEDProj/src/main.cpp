#include <Arduino.h>
const int ledPinNum = 2; 
void setup(){
  pinMode(ledPinNum,OUTPUT);
}

void loop(){
  digitalWrite(ledPinNum, HIGH);
  delay(2000);
  digitalWrite(ledPinNum,LOW);
  delay(2000);
}