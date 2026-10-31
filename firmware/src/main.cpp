// ============================================================================
// Lab-Tool - Firmware integrado do dispositivo (v0.1)
// Placa: ESP32-S3 | Arquitetura em camadas: drivers -> servicos -> apps -> menu
//
// O loop faz sempre 3 passos: ler entrada (botoes) -> atualizar (menu/app) ->
// desenhar (display). O menu lista os apps; cada app implementa a interface App
// (enter/loop/exit). Apps de radio sao stubs ("requer hardware") ate o modulo
// chegar.
// ============================================================================
#include <Arduino.h>
#include "board_pins.h"
#include "Logger.h"
#include "Config.h"
#include "Buttons.h"
#include "Display.h"
#include "Menu.h"
#include "apps/AppInfo.h"
#include "apps/AppLed.h"
#include "apps/AppBuzzer.h"
#include "apps/AppSettings.h"
#include "apps/AppWifiScan.h"
#include "apps/AppStub.h"

// --- servicos / drivers (globais, uma instancia) ---
Config  cfg;
Buttons botoes;
Display tela;

// --- apps ---
AppInfo     appInfo;
AppLed      appLed;
AppBuzzer   appBuzzer;
AppWifiScan appWifi;
AppSettings appSettings;
AppStub     appIR("IR",       "requer hardware");
AppStub     appRFID("RFID",   "requer hardware");
AppStub     appSubGHz("Sub-GHz", "requer hardware");
AppStub     appBLE("BLE",     "Wokwi nao simula BT");

App* lista[] = {
  &appInfo, &appLed, &appBuzzer, &appWifi,
  &appIR, &appRFID, &appSubGHz, &appBLE, &appSettings
};
Menu menu(lista, sizeof(lista) / sizeof(lista[0]));

void setup() {
  Serial.begin(115200);
  delay(200);
  LOG("Lab-Tool firmware v0.1");
  cfg.begin();
  LOG("Boot numero %u", (unsigned)cfg.bootCount());
  botoes.begin();
  tela.begin();
  menu.begin(cfg);
  LOG("Pronto. CIMA/BAIXO navega, OK abre/volta.");
}

void loop() {
  botoes.update();
  menu.update(botoes, tela, cfg);
}
