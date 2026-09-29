#include <Arduino.h>
#include <avr/wdt.h>


void setup() {
  Serial.begin(9600);
  wdt_enable(WDTO_8S);
}

unsigned long counter = 0;
void loop() {
  wdt_reset();
  delay(1000);
  Serial.println(counter);
  counter++; 
  if (counter>=5){
    wdt_reset();
  }
  // put your main code here, to run repeatedly:
}



//add project depencdency 
