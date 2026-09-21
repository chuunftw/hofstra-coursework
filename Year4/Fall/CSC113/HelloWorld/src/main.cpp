#include <Arduino.h>

void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,HIGH); //sets digital pin 13 to 
  delay(1000); 
  digitalWrite(13,LOW);
  delay(1000); 
  digitalWrite(16,HIGH); //sets digital pin 13 to 
  delay(1000); 
  digitalWrite(16,LOW);
  delay(1000); 
}

