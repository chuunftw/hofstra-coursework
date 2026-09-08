#include <Arduino.h>


//
// Based on code taken from: https://www.geeksforgeeks.org/morse-code-implementation/
//
// Function to encode a alphabet as morse code
String morseEncode(char x)
{
  // switch on character
  switch (x) {
  case 'a':
    return ".-";
  case 'b':
    return "-...";
  case 'c':
    return "-.-.";
  case 'd':
    return "-..";
  case 'e':
    return ".";
  case 'f':
    return "..-.";
  case 'g':
    return "--.";
  case 'h':
    return "....";
  case 'i':
    return "..";
  case 'j':
    return ".---";
  case 'k':
    return "-.-";
  case 'l':
    return ".-..";
  case 'm':
    return "--";
  case 'n':
    return "-.";
  case 'o':
    return "---";
  case 'p':
    return ".--.";
  case 'q':
    return "--.-";
  case 'r':
    return ".-.";
  case 's':
    return "...";
  case 't':
    return "-";
  case 'u':
    return "..-";
  case 'v':
    return "...-";
  case 'w':
    return ".--";
  case 'x':
    return "-..-";
  case 'y':
    return "-.--";
  case 'z':
    return "--..";
  default:
	//Serial.println("error unknown code" + x);
	return "";
  }
}

String morseEncode(String s)
{
  // Encode string
	String morseCodeStr;
  for (int i = 0; s[i]; i++)
	  morseCodeStr += morseEncode(s[i]);
  return morseCodeStr;
}

void morseLED(String s)
{
  int time = 300; //300 ms

  for (int i = 0; i < s.length(); i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    if (s[i] == '.')
    {
      delay(time); //how often light flashes of the letters of ryan 
    }
    else if (s[i] == '-')
    {
      delay(time * 3);
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(time);
  }
}
