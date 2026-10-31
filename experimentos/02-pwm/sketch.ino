// ============================================================================
// Experimento 02 — PWM (controlar o BRILHO de um LED)
// Nivel 1/2 | Placa: ESP32-S3 | Ambiente: Wokwi (core Arduino-ESP32 3.x)
//
// Objetivo: sair do "liga/desliga" e controlar a INTENSIDADE do LED.
// Conceitos: PWM, duty cycle (ciclo de trabalho), frequencia, resolucao.
// Circuito: o MESMO do Blink (GPIO2 -> resistor -> LED -> GND). So o codigo mudou.
// ============================================================================

const int LED_PIN  = 2;      // mesmo pino do Blink
const int PWM_FREQ = 5000;   // 5000 Hz: liga/desliga 5000x por segundo (o olho nao ve piscar)
const int PWM_RES  = 8;      // resolucao de 8 bits -> duty de 0 (0%) ate 255 (100%)

void setup() {
  Serial.begin(115200);
  // Configura o PWM por hardware (LEDC) neste pino. So precisa fazer 1 vez.
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  Serial.println("Experimento 02 - PWM (brilho) iniciado");
}

void loop() {
  // Efeito "respiracao": o brilho sobe de 0 a 100% e depois volta.
  Serial.println("Aumentando o brilho: 0 -> 100%");
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(LED_PIN, duty);   // define o brilho (0 = apagado, 255 = maximo)
    delay(8);                   // 8 ms por passo -> subida suave (~2 s)
  }

  Serial.println("Diminuindo o brilho: 100% -> 0");
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(LED_PIN, duty);
    delay(8);
  }
}
