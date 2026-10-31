#pragma once
#include "../App.h"
// App "LED": faz o LED respirar (PWM) - demonstra o pwm_compat.
class AppLed : public App {
public:
  const char* nome() const override { return "LED (PWM)"; }
  void enter(Config& cfg) override;
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
  void exit() override;
private:
  int duty_ = 0;
  int passo_ = 4;
};
