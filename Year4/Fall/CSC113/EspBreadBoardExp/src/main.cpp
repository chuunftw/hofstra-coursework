#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// Constructor for a 0.96-inch SSD1306 128x64 I2C display using U8g2
// U8G2_R0 means no rotation
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Hello World!");
  u8g2.sendBuffer();
  delay(1000);
}

