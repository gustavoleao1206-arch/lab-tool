#pragma once
#include "../App.h"
// App "WiFi Scan": escaneia redes e mostra quantas achou + a primeira
// (SSID/canal/RSSI). Observacao passiva de metadados publicos - escopo seguro.
class AppWifiScan : public App {
public:
  const char* nome() const override { return "WiFi Scan"; }
  void enter(Config& cfg) override;
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
  void exit() override;
private:
  int  n_ = -1;              // -1 = ainda nao escaneou
  char primeiro_[33] = {0};
  int  canal_ = 0;
  int  rssi_ = 0;
};
