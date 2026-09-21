#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(9600);
  Serial.println("waiting for key");
}

void loop(){
  if(Serial.available()>0){
    String test = Serial.readStringUntil('\n'); 
    Serial.println(test);
  }

}