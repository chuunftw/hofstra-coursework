#include <Arduino.h>
const int pin = 2; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(pin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World" );
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);

}
//pin 2 