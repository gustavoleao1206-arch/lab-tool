#include "AppWifiScan.h"
#include "../Buttons.h"
#include "../Display.h"
#include <WiFi.h>
#include <U8g2lib.h>

void AppWifiScan::enter(Config&) {
  n_ = -1;
  primeiro_[0] = 0;
}

void AppWifiScan::exit() {
  WiFi.scanDelete();
}

void AppWifiScan::loop(Buttons& btn, Display& disp, Config&) {
  if (btn.ok()) { sair(); return; }

  if (n_ == -1) {
    // aviso antes de escanear (scanNetworks bloqueia alguns segundos)
    disp.mensagem("WiFi Scan", "Escaneando...", "");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    n_ = WiFi.scanNetworks();
    if (n_ > 0) {
      strncpy(primeiro_, WiFi.SSID(0).c_str(), sizeof(primeiro_) - 1);
      primeiro_[sizeof(primeiro_) - 1] = 0;
      canal_ = WiFi.channel(0);
      rssi_  = WiFi.RSSI(0);
    }
    return;
  }

  U8G2& g = disp.gfx();
  g.clearBuffer();
  g.setFont(u8g2_font_6x10_tr);
  g.drawStr(0, 10, "WiFi Scan");
  char buf[40];
  snprintf(buf, sizeof(buf), "Redes: %d", n_);
  g.drawStr(0, 26, buf);
  if (n_ > 0) {
    g.drawStr(0, 40, primeiro_);
    snprintf(buf, sizeof(buf), "ch:%d  %d dBm", canal_, rssi_);
    g.drawStr(0, 52, buf);
  }
  g.drawStr(0, 62, "OK = voltar");
  g.sendBuffer();
}
