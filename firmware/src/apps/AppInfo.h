#pragma once
#include "../App.h"
// App "Sobre": informacoes do dispositivo (boots, RAM livre, uptime).
class AppInfo : public App {
public:
  const char* nome() const override { return "Sobre"; }
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
};
