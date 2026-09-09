#include <Arduino.h>

// save some chars
const char signMessage[] PROGMEM = {"Give an input"};
const char signText[] PROGMEM = {"Whatever I feel like."};

inline void printFlashString(const char *strMessage)
{
  int strMessageLength = strlen_P(strMessage);
  for (byte k = 0;k<strMessageLength;k++)
  {
    char myChar = (strMessage + k);
    Serial.print(myChar); 
  }
}

void setup(){
  Serial.begin(9600);
  printFlashString(signMessage);
}
    

void loop()
{

}