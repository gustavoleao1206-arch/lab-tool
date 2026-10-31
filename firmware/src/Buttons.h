#pragma once
#include <Arduino.h>
// ============================================================================
// Driver dos 3 botoes (CIMA/BAIXO/OK) com pull-up interno, debounce por tempo
// e deteccao de borda. update() 1x por frame; cima()/baixo()/ok() sao true por
// apenas 1 frame no instante do aperto.
// ============================================================================
class Buttons {
public:
  void begin();
  void update();

  bool cima()  const { return b_[0].borda; }
  bool baixo() const { return b_[1].borda; }
  bool ok()    const { return b_[2].borda; }

private:
  struct B { uint8_t pino; int ant; int est; unsigned long t; bool borda; };
  B b_[3];
};
