// #include <Arduino.h>
// const int buttonPin = 2; 
// int lastDebounceTime =0; 
// const int debounceDelay = 50; 
// bool buttonState = false; 
// bool lastButtonState = false;


// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(buttonPin, INPUT);
// }

// void loop() {
//     // read the state of the switch into a local variable:
//     int reading = digitalRead(buttonPin);
//     //Serial.print(reading);
//     //delay(100);
//     // check to see if you just pressed the button
//     // (i.e. the input went from LOW to HIGH), and you've waited long enough
//     // since the last press to ignore any noise:

//     // If the switch changed, due to noise or pressing:
//     if (reading != lastButtonState) {
//       // reset the debouncing timer
//       lastDebounceTime = millis();
//     }

//     if ((millis() - lastDebounceTime) > debounceDelay) {
//       // whatever the reading is at, it's been there for longer than the debounce
//       // delay, so take it as the actual current state:

//       // if the button state has changed:
//       if (reading != buttonState){
//         buttonState = reading;
//         Serial.println(buttonState);
//       }q

//     // save the reading. Next time through the loop, it'll be the lastButtonState:
//     lastButtonState = reading;
    
//   }
// }

#include <Arduino.h>
const int pinNum = 2;
const int ledNum = 13;

void setup(){
  pinMode(pinNum, INPUT_PULLUP);
  pinMode(ledNum, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(100);
  int val = digitalRead(pinNum);
  if (val == 0 ){
    digitalWrite(ledNum, HIGH);
  }
  else{
    digitalWrite(ledNum,LOW);
  }
}