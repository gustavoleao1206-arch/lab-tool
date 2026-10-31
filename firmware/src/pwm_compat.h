#pragma once
#include <Arduino.h>
// ============================================================================
// Compatibilidade do PWM/LEDC entre Arduino-ESP32 core 2.x e 3.x.
//  - core 3.x: ledcAttach(pino, freq, res) / ledcWrite(pino, duty) / ledcWriteTone(pino, freq)
//  - core 2.x: ledcSetup(canal, freq, res) + ledcAttachPin(pino, canal) / ledcWrite(canal, ...)
// Como os apps usam PWM um de cada vez (LED OU buzzer), reutilizamos o canal 0.
// ============================================================================
#define PWM_CANAL_COMPAT 0

inline void pwmAttach(uint8_t pin, uint32_t freq, uint8_t res) {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcAttach(pin, freq, res);
#else
  ledcSetup(PWM_CANAL_COMPAT, freq, res);
  ledcAttachPin(pin, PWM_CANAL_COMPAT);
#endif
}

inline void pwmWrite(uint8_t pin, uint32_t duty) {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcWrite(pin, duty);
#else
  (void)pin;
  ledcWrite(PWM_CANAL_COMPAT, duty);
#endif
}

inline void pwmTone(uint8_t pin, uint32_t freq) {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcWriteTone(pin, freq);
#else
  (void)pin;
  ledcWriteTone(PWM_CANAL_COMPAT, freq);
#endif
}

inline void pwmDetach(uint8_t pin) {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  ledcDetach(pin);
#else
  ledcDetachPin(pin);
#endif
}
