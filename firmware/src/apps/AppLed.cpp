#include "AppLed.h"
#include "../Buttons.h"
#include "../Display.h"
#include "../board_pins.h"
#include "../pwm_compat.h"
#include <U8g2lib.h>

void AppLed::enter(Config&) {
  pwmAttach(PIN_LED, 5000, 8);
  duty_ = 0;
  passo_ = 4;
}

void AppLed::exit() {
  pwmWrite(PIN_LED, 0);
  pwmDetach(PIN_LED);
}

void AppLed::loop(Buttons& btn, Display& disp, Config&) {
  if (btn.ok()) { sair(); return; }

  duty_ += passo_;
  if (duty_ >= 255) { duty_ = 255; passo_ = -passo_; }
  if (duty_ <= 0)   { duty_ = 0;   passo_ = -passo_; }
  pwmWrite(PIN_LED, duty_);

  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 10, "LED respirando (PWM)");
  int w = map(duty_, 0, 255, 0, 120);
  g.drawFrame(0, 24, 122, 12);
  g.drawBox(1, 25, w, 10);
  char buf[20];
  snprintf(buf, sizeof(buf), "duty: %d/255", duty_);
  g.drawStr(0, 50, buf);
  g.drawStr(0, 62, "OK = voltar");
  g.sendBuffer();
  delay(10);
}
