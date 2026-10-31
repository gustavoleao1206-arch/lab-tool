#include "Display.h"
#include "board_pins.h"

// Construtor U8g2: (rotacao, reset, SCL, SDA). A U8g2 chama Wire.begin(SDA,SCL).
Display::Display()
  : u8g2_(U8G2_R0, U8X8_PIN_NONE, PIN_I2C_SCL, PIN_I2C_SDA) {}

void Display::begin() {
  u8g2_.begin();
}

U8G2& Display::gfx() {
  return u8g2_;
}

void Display::mensagem(const char* titulo, const char* linha1, const char* linha2) {
  u8g2_.clearBuffer();
  u8g2_.setFont(u8g2_font_7x13_tr);
  u8g2_.drawStr(0, 14, titulo);
  u8g2_.setFont(u8g2_font_6x10_tr);
  u8g2_.drawStr(0, 36, linha1);
  u8g2_.drawStr(0, 50, linha2);
  u8g2_.sendBuffer();
}
