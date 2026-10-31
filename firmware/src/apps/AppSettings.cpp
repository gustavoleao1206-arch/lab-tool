#include "AppSettings.h"
#include "../Buttons.h"
#include "../Display.h"
#include "../Config.h"
#include "../board_pins.h"
#include "../pwm_compat.h"
#include <U8g2lib.h>

void AppSettings::enter(Config& cfg) {
  brilho_ = cfg.brilho();
  pwmAttach(PIN_LED, 5000, 8);
  pwmWrite(PIN_LED, brilho_);
}

void AppSettings::exit() {
  pwmWrite(PIN_LED, 0);
  pwmDetach(PIN_LED);
}

void AppSettings::loop(Buttons& btn, Display& disp, Config& cfg) {
  if (btn.cima())  { brilho_ += 16; if (brilho_ > 255) brilho_ = 255; pwmWrite(PIN_LED, brilho_); }
  if (btn.baixo()) { brilho_ -= 16; if (brilho_ < 0)   brilho_ = 0;   pwmWrite(PIN_LED, brilho_); }
  if (btn.ok())    { cfg.setBrilho((uint8_t)brilho_); sair(); return; }

  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 10, "Config: brilho do LED");
  int w = map(brilho_, 0, 255, 0, 120);
  g.drawFrame(0, 24, 122, 12);
  g.drawBox(1, 25, w, 10);
  char buf[20];
  snprintf(buf, sizeof(buf), "brilho: %d", brilho_);
  g.drawStr(0, 48, buf);
  g.drawStr(0, 62, "CIMA/BAIXO  OK=salvar");
  g.sendBuffer();
}
