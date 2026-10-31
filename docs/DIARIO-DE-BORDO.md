# Diário de Bordo

Registro das etapas de desenvolvimento, decisões e lições aprendidas.

## Análise e arquitetura

- Arquitetura da V1 definida: MCU **ESP32-S3** (ver [DECISOES-TECNICAS.md](DECISOES-TECNICAS.md)).
- Estratégia: validar no simulador (Wokwi) antes de comprar hardware; integrar um módulo por vez.
- Roadmap de 10 níveis: eletrônica → MCU → display → armazenamento → comunicação → módulos →
  firmware → PCB → portátil → V2/V3.

## Níveis 1–4 — fundamentos do firmware (Wokwi)

Experimentos 01–08 construídos e validados no simulador:

- 01 Blink · 02 PWM · 03 Buzzer · 04 Botões + debounce · 05 ADC · 06 OLED (U8g2) ·
  07 Menu navegável · 08 NVS (config persistente).

Lições:

- A aba do simulador em segundo plano roda devagar — em testes de botão foi preciso reduzir o
  debounce para captar o clique; o valor correto (40/25 ms) fica nos arquivos.
- O editor do Wokwi às vezes junta o primeiro `#include` com a linha seguinte, e autocompleta
  `<WiFi.h>` para `<WiFiNINA.h>` (placa errada) — conferir o topo do código após colar.
- Os experimentos de display/menu precisam da biblioteca **U8g2**.

## Versionamento

- Projeto versionado em Git e publicado no GitHub.

## Nível 5 — Comunicação (WiFi no simulador)

- Exp 09 (WiFi Scanner) e Exp 10 (conectar + HTTP GET) validados no Wokwi: rede virtual
  `Wokwi-GUEST`, IP 10.10.0.2 via gateway, GET em `example.com` → HTTP 200.
- BLE e ESP-NOW não rodam no Wokwi (Bluetooth não é simulado) → ficam para o hardware real.

## Nível 7 — firmware integrado (v0.1)

- Os experimentos foram unificados num **firmware modular** (projeto PlatformIO) com arquitetura
  em camadas (drivers → serviços → apps → menu). Cada app pluga pela mesma interface.
- Apps: Sobre, LED (PWM), Buzzer, WiFi Scan, Config (NVS) + stubs (IR/RFID/Sub-GHz/BLE).
- Próximo: hardware físico (protoboard) → módulos (Nível 6) → PCB → portátil.
