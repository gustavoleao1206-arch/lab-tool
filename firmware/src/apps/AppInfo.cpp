#include "AppInfo.h"
#include "../Buttons.h"
#include "../Display.h"
#include "../Config.h"
#include <U8g2lib.h>

void AppInfo::loop(Buttons& btn, Display& disp, Config& cfg) {
  if (btn.ok()) { sair(); return; }
  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 8, "Lab-Tool v0.1");
  g.drawHLine(0, 11, 128);
  char buf[32];
  snprintf(buf, sizeof(buf), "Boots: %u", (unsigned)cfg.bootCount());
  g.drawStr(0, 24, buf);
  snprintf(buf, sizeof(buf), "RAM livre: %u", (unsigned)ESP.getFreeHeap());
  g.drawStr(0, 36, buf);
  snprintf(buf, sizeof(buf), "Uptime: %lus", (unsigned long)(millis() / 1000));
  g.drawStr(0, 48, buf);
  g.drawStr(0, 62, "OK = voltar");
  g.sendBuffer();
}
