#include "Menu.h"
#include "Buttons.h"
#include "Display.h"
#include "Config.h"
#include <U8g2lib.h>

void Menu::begin(Config&) {
  sel_ = 0;
  ativo_ = nullptr;
}

void Menu::update(Buttons& btn, Display& disp, Config& cfg) {
  if (ativo_ == nullptr) {
    // --- navegacao do menu ---
    if (btn.cima())  sel_ = (sel_ - 1 + n_) % n_;
    if (btn.baixo()) sel_ = (sel_ + 1) % n_;
    if (btn.ok()) {
      ativo_ = apps_[sel_];
      ativo_->limparSair();
      ativo_->enter(cfg);
      return;
    }
    desenhar(disp);
  } else {
    // --- app ativo ---
    ativo_->loop(btn, disp, cfg);
    if (ativo_->querSair()) {
      ativo_->exit();
      ativo_ = nullptr;
      desenhar(disp);
    }
  }
}

void Menu::desenhar(Display& disp) {
  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 8, "Lab-Tool");
  g.drawHLine(0, 11, 128);

  // janela rolavel: mostra ate 5 itens em volta do selecionado
  int linhas = (n_ < 5) ? n_ : 5;
  int inicio = 0;
  if (n_ > 5) {
    inicio = sel_ - 2;
    if (inicio < 0) inicio = 0;
    if (inicio > n_ - 5) inicio = n_ - 5;
  }
  for (int row = 0; row < linhas; row++) {
    int i = inicio + row;
    int y = 22 + row * 10;
    if (i == sel_) {
      g.drawBox(0, y - 8, 128, 10);
      g.setDrawColor(0);
      g.drawStr(3, y, apps_[i]->nome());
      g.setDrawColor(1);
    } else {
      g.drawStr(3, y, apps_[i]->nome());
    }
  }
  g.sendBuffer();
}
