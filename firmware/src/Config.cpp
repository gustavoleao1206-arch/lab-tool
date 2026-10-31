#include "Config.h"

void Config::begin() {
  prefs_.begin("labtool", false);          // leitura+escrita
  boots_  = prefs_.getUInt("boots", 0) + 1; // incrementa a cada boot
  prefs_.putUInt("boots", boots_);
  brilho_ = prefs_.getUChar("brilho", 128);
  volume_ = prefs_.getUChar("volume", 5);
  prefs_.end();
}

void Config::setBrilho(uint8_t v) {
  brilho_ = v;
  prefs_.begin("labtool", false);
  prefs_.putUChar("brilho", v);
  prefs_.end();
}

void Config::setVolume(uint8_t v) {
  volume_ = v;
  prefs_.begin("labtool", false);
  prefs_.putUChar("volume", v);
  prefs_.end();
}
