// ============================================================================
// Experimento 09 - WiFi Scanner (metadados publicos) - Nivel 5
// ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x | sem bibliotecas (WiFi.h e nativa)
//
// Le os metadados PUBLICOS das redes WiFi ao redor: SSID, canal, RSSI (forca
// do sinal) e tipo de seguranca. E observacao passiva - escopo seguro (como
// ler a placa de uma loja; a rede se anuncia publicamente no beacon).
//
// NOTA sobre o Wokwi: o simulador tem UMA rede virtual aberta "Wokwi-GUEST"
// (canal 6). No plano gratis o scan mostra SO ela (redes falsas extras sao
// recurso pago). No HARDWARE REAL, este mesmo codigo lista todas as redes
// de verdade ao seu redor.
//
// Conceitos:
//  - WiFi.scanNetworks() devolve quantas redes achou.
//  - Para cada: WiFi.SSID(i), WiFi.channel(i), WiFi.RSSI(i), encryptionType(i).
//  - RSSI em dBm (negativo; mais perto de 0 = mais forte).
//  - seg = enum WIFI_AUTH_* (0 = OPEN/aberta, ... WPA2_PSK, WPA3_PSK, etc).
//  - Em 2,4 GHz os canais 1, 6 e 11 nao se sobrepoem.
//
// GOTCHA do editor Wokwi: ao digitar "#include <WiFi.h>" o autocomplete pode
// trocar por "<WiFiNINA.h>" (biblioteca de OUTRA placa!). Confira: e WiFi.h.
// ============================================================================

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(300);
  WiFi.mode(WIFI_STA);   // modo estacao (cliente) - necessario para escanear
  WiFi.disconnect();
  delay(100);
  Serial.println("Experimento 09 - WiFi Scanner");
}

void loop() {
  Serial.println("Escaneando redes...");
  int n = WiFi.scanNetworks();
  Serial.printf("Redes encontradas: %d\n", n);
  for (int i = 0; i < n; i++) {
    Serial.printf("%2d) %-20s canal:%2d  %4d dBm  seg:%d\n",
      i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i),
      WiFi.RSSI(i), (int)WiFi.encryptionType(i));
  }
  WiFi.scanDelete();
  Serial.println("---");
  delay(5000);
}
