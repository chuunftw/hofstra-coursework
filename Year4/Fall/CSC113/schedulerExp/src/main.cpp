#include <Arduino.h>
#include "scheduler.h"

void function_handler_1(){
  digitalWrite(13,HIGH);
}

void function_handler_2(){
  digitalWrite(13,LOW);
}
void setup() {
  Serial.begin(9600);
  add_task(100, function_handler_1);
  add_task(200, function_handler_2);
  inti_scheduler();
}

void loop() {
  
}

