#include "AppStub.h"
#include "../Buttons.h"
#include "../Display.h"
#include <U8g2lib.h>

void AppStub::loop(Buttons& btn, Display& disp, Config&) {
  if (btn.ok()) { sair(); return; }
  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_7x13_tr);
  g.drawStr(0, 16, nome_);
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 36, motivo_);
  g.drawStr(0, 50, "(em breve)");
  g.drawStr(0, 62, "OK = voltar");
  g.sendBuffer();
}
