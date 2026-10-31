// ============================================================================
// Experimento 08 - Config persistente (NVS / Preferences) - Nivel 4
// ESP32-S3 (Wokwi) | core 3.x | Biblioteca Preferences (NATIVA, sem instalar)
//
// Guarda na flash (NVS) um "contador de boots" que sobe a cada reinicio e
// NAO some ao desligar, e uma config pequena (brilho do LED). Usa o brilho
// salvo para acender o LED (GPIO2) meio-aceso.
//
// Conceitos: RAM (some ao desligar) vs flash/NVS (persiste); NVS = armario
// chave-valor na flash; namespace separa suas chaves; getUInt(chave, padrao)
// devolve o padrao no 1o boot. Config pequena -> NVS; captura grande -> SD.
//
// Nota: no Wokwi a flash pode zerar ao recarregar a pagina; o ponto e a API
// e o conceito. No hardware real o valor persiste de verdade.
// ============================================================================

#include <Preferences.h>

Preferences prefs;

const int PINO_LED  = 2;
const int FREQ_PWM  = 5000;
const int RESOLUCAO = 8;

void setup() {
  Serial.begin(115200);
  delay(300);

  prefs.begin("labtool", false);                 // abre namespace (leitura+escrita)
  unsigned int boots = prefs.getUInt("boots", 0); // 0 no primeiro boot
  boots = boots + 1;
  prefs.putUInt("boots", boots);                  // salva de volta na flash

  unsigned int brilho = prefs.getUInt("brilho", 128);
  prefs.putUInt("brilho", brilho);
  prefs.end();                                    // fecha o namespace

  Serial.print("Boot numero ");  Serial.println(boots);
  Serial.print("Brilho salvo: "); Serial.println(brilho);

  ledcAttach(PINO_LED, FREQ_PWM, RESOLUCAO);      // usa a config: LED no brilho salvo
  ledcWrite(PINO_LED, brilho);
}

void loop() {
  delay(1000);   // aperte o RESET da placa no Wokwi para ver o contador subir
}
