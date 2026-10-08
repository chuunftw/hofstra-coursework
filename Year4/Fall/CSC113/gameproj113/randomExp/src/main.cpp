#include <Arduino.h>

const int green = 2;
const int yellow = 3;
const int listOfRandomSize = 20;
int rangeRandom = 4;
int randNumber;
int listOfRandom[listOfRandomSize];

void setup() {
  Serial.begin(9600);
  int seed = analogRead(A0);
  Serial.println(seed);
  randomSeed(seed);
  Serial.println("beginning");
}

void loop() {
  randNumber = random(300);
  for (int i = 0; i < listOfRandomSize; i++) {
    listOfRandom[i] = random(rangeRandom);
  }
  Serial.println(randNumber);
  delay(500);
}
