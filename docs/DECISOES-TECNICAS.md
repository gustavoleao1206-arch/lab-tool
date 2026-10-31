# Decisões Técnicas (ADR — Architecture Decision Records, formato resumido)

## ADR-001 — MCU da V1: ESP32-S3

**Data:** 2026-08-25 · **Status:** aceito

**Contexto:** o dispositivo é um anfitrião que orquestra rádios/periféricos; o usuário é
iniciante e quer aprender a sério, com facilidade de destravar dúvidas.

**Decisão:** usar **ESP32-S3** (placa ESP32-S3-DevKitC-1, variante N16R8 = 16 MB Flash / 8 MB PSRAM)
como cérebro da V1.

**Justificativa:**
- WiFi + BLE 5 nativos → dispensa rádio externo para começar.
- USB OTG nativo (HID/mass-storage) + **JTAG por USB nativo** → debug sem hardware extra.
- RAM/PSRAM/Flash generosas → sobra para UI, sistema de arquivos, buffers e logs.
- Ecossistema enorme (Arduino-ESP32, ESP-IDF, PlatformIO) → suporte e bibliotecas.
- Opera em 3,3 V → casa naturalmente com os módulos (RC522, CC1101, nRF24 são 3,3 V).

**Alternativas consideradas (mantidas como estudo paralelo, não como base da V1):**
ESP32-WROOM-32 (mais barato, migração fácil), RP2040/Pico (PIO para timings de RF/RFID),
STM32 "Blue Pill" (didática bare-metal), nRF52840 (ultrabaixo consumo).

## ADR-002 — Começar no simulador Wokwi

**Data:** 2026-08-25 · **Status:** aceito

**Decisão:** validar os Níveis 1–3 no **Wokwi** antes de comprar hardware.

**Justificativa:** custo zero, iteração instantânea, sem risco elétrico. Ideal para consolidar
os fundamentos (GPIO, ADC, PWM, display, menus) antes de investir em componentes.
