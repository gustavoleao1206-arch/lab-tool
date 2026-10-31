// ============================================================================
// Experimento 01 — Blink (piscar um LED)
// Nivel 1 (Eletronica basica) | Placa: ESP32-S3 | Ambiente: Wokwi (simulador)
//
// Objetivo: controlar um GPIO como SAIDA digital para acender/apagar um LED.
// Conceitos: GPIO, nivel logico (HIGH = ~3,3 V, LOW = 0 V), tempo (delay), setup/loop.
// ============================================================================

// GPIO2 -> resistor 220 ohm -> LED (anodo) ... LED (catodo) -> GND
const int LED_PIN = 2;   // "const int": um numero fixo com nome. Evita "numero magico" solto.

// setup(): roda UMA vez quando a placa liga.
void setup() {
  Serial.begin(115200);         // abre a comunicacao serial a 115200 bps (para imprimir texto)
  pinMode(LED_PIN, OUTPUT);     // configura o GPIO2 como SAIDA digital
  Serial.println("Experimento 01 - Blink iniciado");
}

// loop(): roda PARA SEMPRE, repetindo, depois do setup().
void loop() {
  digitalWrite(LED_PIN, HIGH);  // coloca ~3,3 V no pino -> LED ACENDE
  Serial.println("LED: ON");
  delay(500);                   // pausa de 500 ms (meio segundo)

  digitalWrite(LED_PIN, LOW);   // coloca 0 V no pino -> LED APAGA
  Serial.println("LED: OFF");
  delay(500);                   // pausa de 500 ms
}
