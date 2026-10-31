// ============================================================================
// Experimento 06 - Display OLED SSD1306 128x64 (I2C)
// Nivel 3 | ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x
// BIBLIOTECA NECESSARIA no Wokwi: "U8g2" (Library Manager -> + -> U8g2)
//
// Mostra "Lab-Tool" + um contador que sobe 1/segundo (tambem no Serial).
// Ligacao I2C (2 fios), tudo 3,3V: SDA=GPIO8, SCL=GPIO9, VCC=3V3, GND=GND.
//
// Conceitos: I2C (2 fios + endereco 0x3C) vs SPI; framebuffer e o ciclo
// clearBuffer -> desenha -> sendBuffer (desenha na RAM e envia de uma vez).
// Construtor U8g2 p/ SSD1306 128x64 HW I2C: parametros (rot, reset, SCL, SDA).
// ============================================================================

#include <U8g2lib.h>

// A U8g2 chama Wire.begin(SDA, SCL) = Wire.begin(8, 9) sozinha.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, 9, 8);

unsigned long contador = 0;
unsigned long ultimoSeg = 0;

void desenha(unsigned long v) {
  char num[12];
  sprintf(num, "%lu", v);
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB10_tr);
  display.drawStr(0, 14, "Lab-Tool");
  display.drawHLine(0, 20, 128);
  display.setFont(u8g2_font_6x13_tr);
  display.drawStr(0, 36, "Contador:");
  display.setFont(u8g2_font_logisoso24_tn);
  display.drawStr(0, 62, num);
  display.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  display.begin();          // inicia o OLED e o I2C em SDA=8 / SCL=9
  desenha(contador);
}

void loop() {
  if (millis() - ultimoSeg >= 1000) {
    ultimoSeg = millis();
    contador++;
    Serial.print("Contador: "); Serial.println(contador);
    desenha(contador);
  }
}
