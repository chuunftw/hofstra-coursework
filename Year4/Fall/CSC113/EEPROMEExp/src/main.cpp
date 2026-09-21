#include <Arduino.h>
#include <EEPROM.h>
#define LIMIT 94
void writeData(){
  for(int i = 0; i<LIMIT;i++){
    EEPROM.write(i,i+33);
  }
}

void readData(){
  for (int i =0; i<LIMIT; i++){
    byte val = EEPROM.read(i);
    Serial.println(char(val));
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //writeData();
  readData();
}

void loop() {
  // put your main code here, to run repeatedly:
}

