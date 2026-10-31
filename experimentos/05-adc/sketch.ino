// ============================================================================
// Experimento 05 - ADC (potenciometro)
// Nivel 2 | ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x | sem bibliotecas
//
// Le a tensao de um potenciometro (SIG no GPIO1 / ADC1) e mostra no Serial:
// valor bruto (0..4095), porcentagem e tensao aproximada (0..3,3V).
//
// Conceitos: ADC de 12 bits (2^12 = 4096 niveis -> 0..4095); regra de tres
// p/ converter; o ADC do ESP32 nao e perfeitamente linear (use
// analogReadMilliVolts p/ leitura calibrada); ADC2 conflita com WiFi -> ADC1.
// ============================================================================

const int   PINO_POT = 1;      // ADC1
const float VREF     = 3.3;
const int   ADC_MAX  = 4095;

void setup() {
  Serial.begin(115200);
  delay(200);
  analogReadResolution(12);    // garante 12 bits (0..4095)
  Serial.println("Experimento 05 - ADC (potenciometro)");
  Serial.println("Gire o potenciometro.");
}

void loop() {
  int   bruto = analogRead(PINO_POT);
  float pct   = (bruto * 100.0) / ADC_MAX;
  float v     = (bruto * VREF) / ADC_MAX;
  Serial.print("Bruto: "); Serial.print(bruto);
  Serial.print("  |  ");   Serial.print(pct, 1);
  Serial.print(" %  |  "); Serial.print(v, 2); Serial.println(" V");
  delay(500);
}
