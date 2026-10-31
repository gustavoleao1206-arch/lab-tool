#pragma once
#include "../App.h"
// App "stub" (reutilizavel): placeholder para funcoes que ainda dependem de
// hardware (IR, RFID, Sub-GHz, BLE). Ja ocupa o lugar no menu com a mesma
// interface; quando o modulo chegar, troca-se por um app real.
class AppStub : public App {
public:
  AppStub(const char* nome, const char* motivo) : nome_(nome), motivo_(motivo) {}
  const char* nome() const override { return nome_; }
  void loop(Buttons& btn, Display& disp, Config& cfg) override;
private:
  const char* nome_;
  const char* motivo_;
};
