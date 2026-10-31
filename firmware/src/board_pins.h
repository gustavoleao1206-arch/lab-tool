#pragma once
// ============================================================================
// Mapa de pinos do dispositivo Lab-Tool (ESP32-S3) - um unico lugar.
// Mudou a fiacao/PCB? Muda so aqui.
// ============================================================================
#define PIN_LED        2    // LED de status (via resistor -> GND)
#define PIN_BUZZER     4    // buzzer passivo
#define PIN_BTN_CIMA   5    // botao CIMA   (INPUT_PULLUP, outro lado ao GND)
#define PIN_BTN_BAIXO  6    // botao BAIXO
#define PIN_BTN_OK     7    // botao OK
#define PIN_I2C_SDA    8    // OLED SDA
#define PIN_I2C_SCL    9    // OLED SCL
