#include <Arduino.h>
#include "TemplateMorseCode.h"

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  String code = morseEncode("ryan");

  for (int count = 0; count < 8; count++)
  {
    Serial.println(code);
    morseLED(code);
    delay(2000); //pauses between ryans 
  }
}

void loop()
 ZZ}
```32