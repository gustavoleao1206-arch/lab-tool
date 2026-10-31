#include "Buttons.h"
#include "board_pins.h"

static const unsigned long DEBOUNCE_MS = 25;

void Buttons::begin() {
  const uint8_t pinos[3] = { PIN_BTN_CIMA, PIN_BTN_BAIXO, PIN_BTN_OK };
  for (int i = 0; i < 3; i++) {
    b_[i].pino = pinos[i];
    pinMode(pinos[i], INPUT_PULLUP);
    int l = digitalRead(pinos[i]);
    b_[i].ant = l;
    b_[i].est = l;
    b_[i].t = millis();
    b_[i].borda = false;
  }
}

void Buttons::update() {
  unsigned long agora = millis();
  for (int i = 0; i < 3; i++) {
    b_[i].borda = false;
    int l = digitalRead(b_[i].pino);
    if (l != b_[i].ant) { b_[i].ant = l; b_[i].t = agora; }   // reinicia o relogio
    if (agora - b_[i].t > DEBOUNCE_MS) {                      // leitura estavel
      if (l != b_[i].est) {
        b_[i].est = l;
        if (b_[i].est == LOW) b_[i].borda = true;             // borda de descida = aperto
      }
    }
  }
}
