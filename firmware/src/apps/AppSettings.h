#pragma once
#include "../App.h"
// App "Config": ajusta o brilho (CIMA/BAIXO), mostra no LED em tempo real,
// e salva na NVS ao confirmar com OK.
class AppSettings : public App {
public:
  const char* nome() const override { return "Config"; }
  void enter(Config& cfg) override;
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
  void exit() override;
private:
  int brilho_ = 128;
};
