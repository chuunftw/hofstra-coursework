#include <Arduino.h>
enum States {state1 = 1, state2 = 3, state3 = 8 , state4 = 10, state5 = 5};

States S;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  S = state3;
}

void loop() {
  // put your main code here, to run repeatedly:
  int num = -1;
  if (Serial.available()){
    Serial.println("in ");
    num = Serial.parseInt();
    if (num == 1){
      S = state5;
      Serial.println("out ");
    } 
  }
  switch(S){
    case state1:
    S = state2;
    Serial.println("Transitioning from state1 to state2");
    break;

    case state2:
    S = state3;
    Serial.println("Transitioning from state2 to state3");
    break;

    case state3:
    S = state4;
    Serial.println("Transitioning from state3 to state4");
    break;

    case state4:
    S = state1;
    //delay(100);
    Serial.println("Transitioning from state4 to state1");
    break;

    case state5:
    S = state1;
    Serial.println("in state 5");
    break;
  }
  //delay(1000);
}

