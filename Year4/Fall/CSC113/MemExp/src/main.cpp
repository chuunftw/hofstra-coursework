#include <Arduino.h>
#include <EEPROM.h>


const char prompt[] PROGMEM = "Enter a message";
const char savedLabel[] PROGMEM = "EEPROM contains: ";

void printFlashString(const char *message)
{
  int messageLength = strlen_P(message);

  for (int i = 0; i < messageLength; i++)
  {
    Serial.print((char)pgm_read_byte(message + i));
  }
}

void saveSerialInputToEEPROM()
{
  int address = 0;
  int memorySize = EEPROM.length();
  bool receivingMessage = true;

  while (receivingMessage == true)
  {
    if (Serial.available() > 0)
    {
      char currentCharacter = Serial.read();

      if (currentCharacter == '\n')
      {
        receivingMessage = false;
      }
      else if (currentCharacter != '\r' && address < memorySize - 1)
      {
        EEPROM.update(address, currentCharacter);
        address++;
      }
    }
  }
  EEPROM.update(address, '\0');
}

void printEEPROMMessage()
{
  int address = 0;
  int memorySize = EEPROM.length();
  bool endOfMessage = false;

  while (address < memorySize && endOfMessage == false)
  {
    char currentCharacter = EEPROM.read(address);
    
    if (currentCharacter == '\0')
    {
      endOfMessage = true;
    }
    else
    {
      Serial.print(currentCharacter);
      address++;
    }
  }
}

void setup()
{
  Serial.begin(9600);

  printFlashString(prompt);
  Serial.println();

  saveSerialInputToEEPROM();

  printFlashString(savedLabel);
  printEEPROMMessage();
  Serial.println();
}

void loop()
{

}
