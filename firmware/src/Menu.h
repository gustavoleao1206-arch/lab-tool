#pragma once
#include "App.h"
// ============================================================================
// Sistema de menu: recebe uma lista de App* e cuida da navegacao.
// Maquina de estados minima: no menu (ativo_ == nullptr) OU dentro de um app.
// Lista rolavel (mostra ate 5 itens em volta da selecao).
// ============================================================================
class Buttons;
class Display;
class Config;

class Menu {
public:
  Menu(App** apps, int n) : apps_(apps), n_(n) {}
  void begin(Config& cfg);
  void update(Buttons& btn, Display& disp, Config& cfg);

private:
  void desenhar(Display& disp);
  App** apps_;
  int   n_;
  int   sel_   = 0;
  App*  ativo_ = nullptr;   // nullptr = estamos no menu
};
