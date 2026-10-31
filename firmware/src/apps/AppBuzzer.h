#pragma once
#include "../App.h"
// App "Buzzer": toca Do-Re-Mi-Fa-Sol (PWM = frequencia = nota).
class AppBuzzer : public App {
public:
  const char* nome() const override { return "Buzzer"; }
  void enter(Config& cfg) override;
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
  void exit() override;
private:
  int idx_ = 0;
  unsigned long t_ = 0;
};
