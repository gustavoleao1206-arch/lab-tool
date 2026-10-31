#pragma once
#include <Arduino.h>
// ============================================================================
// Log simples com timestamp (ms). Uso: LOG("boot %u", n);
// Em v0.1 so imprime no Serial; depois podemos adicionar sink no SD.
// ============================================================================
#define LOG(fmt, ...) do { Serial.printf("[%8lu] " fmt "\n", (unsigned long)millis(), ##__VA_ARGS__); } while (0)
