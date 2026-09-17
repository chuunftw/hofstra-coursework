#include <Arduino.h>
int analogPin =21; 
int val =0; 
void setup() {
  Serial.begin(9600); 
  pinMode(analogPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin); 
  Serial.println(val);
  delay(100);
}

