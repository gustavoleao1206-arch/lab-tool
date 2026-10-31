#pragma once
#include <U8g2lib.h>
// ============================================================================
// Driver do display OLED SSD1306 128x64 (I2C) via U8g2.
// Expoe o objeto U8g2 (gfx()) para os apps desenharem livremente, e um atalho
// mensagem() para telas simples de texto.
// ============================================================================
class Display {
public:
  Display();
  void begin();
  U8G2& gfx();                        // acesso direto ao U8g2 para desenhar
  void mensagem(const char* titulo, const char* linha1, const char* linha2 = "");

private:
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_;
};
