#pragma once
#include <Preferences.h>
// ============================================================================
// Servico de configuracao persistente (NVS via Preferences).
// Guarda ajustes pequenos que sobrevivem ao desligar: brilho, volume, e um
// contador de boots. Namespace "labtool".
// ============================================================================
class Config {
public:
  void begin();                       // abre NVS, le valores, incrementa boots
  uint32_t bootCount() const { return boots_; }

  uint8_t brilho() const { return brilho_; }     // 0..255
  void    setBrilho(uint8_t v);

  uint8_t volume() const { return volume_; }      // 0..10
  void    setVolume(uint8_t v);

private:
  Preferences prefs_;
  uint32_t boots_  = 0;
  uint8_t  brilho_ = 128;
  uint8_t  volume_ = 5;
};
