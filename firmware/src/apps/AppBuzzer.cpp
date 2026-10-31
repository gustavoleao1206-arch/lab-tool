#include "AppBuzzer.h"
#include "../Buttons.h"
#include "../Display.h"
#include "../board_pins.h"
#include "../pwm_compat.h"
#include <U8g2lib.h>

static const char* NOMES[] = { "Do", "Re", "Mi", "Fa", "Sol" };
static const int    FREQS[] = { 262, 294, 330, 349, 392 };
static const int    N_NOTAS = 5;

void AppBuzzer::enter(Config&) {
  pwmAttach(PIN_BUZZER, 1000, 10);
  idx_ = 0;
  t_ = millis();
  pwmTone(PIN_BUZZER, FREQS[idx_]);
}

void AppBuzzer::exit() {
  pwmTone(PIN_BUZZER, 0);
  pwmDetach(PIN_BUZZER);
}

void AppBuzzer::loop(Buttons& btn, Display& disp, Config&) {
  if (btn.ok()) { sair(); return; }

  unsigned long agora = millis();
  if (agora - t_ > 500) {
    t_ = agora;
    idx_ = (idx_ + 1) % N_NOTAS;
    pwmTone(PIN_BUZZER, FREQS[idx_]);
  }

  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 10, "Buzzer: PWM = nota");
  g.setFont(u8g2_font_9x15_tr);
  g.drawStr(24, 42, NOMES[idx_]);
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 62, "OK = voltar");
  g.sendBuffer();
}
