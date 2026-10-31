# Lab-Tool

> [🇬🇧 English](README.md) · 🇧🇷 **Português**

Um multiferramenta portátil de laboratório, conceitualmente inspirado no Flipper Zero, construído
**do zero** num **ESP32-S3** como forma prática de aprender eletrônica, sistemas embarcados,
firmware, RF e protocolos digitais.

> ⚠️ **Uso exclusivamente educacional.** Tudo aqui é feito para ser testado em **equipamentos
> próprios ou com autorização explícita**. Sem jamming, sem clonagem de credenciais de terceiros,
> sem invasão ou interceptação. Temas dual-use são estudados apenas na versão segura de
> laboratório, respeitando a regulamentação de rádio local.

## Status

- **Níveis 1–4 (fundamentos do firmware)** validados no simulador [Wokwi](https://wokwi.com):
  GPIO, PWM, buzzer, botões + debounce, ADC, display OLED, menu navegável, config persistente (NVS).
- **Nível 5 (WiFi)** validado no simulador: scan de redes + conexão + requisição HTTP.
- **Nível 7 (firmware integrado):** os experimentos foram unificados num firmware modular
  (PlatformIO) que compila para o ESP32-S3.
- **Próximo:** hardware físico → módulos de rádio (IR, RFID, Sub-GHz) → PCB própria → versão portátil.

## Arquitetura (V1)

- **MCU:** ESP32-S3 (ESP32-S3-DevKitC-1) — WiFi/BLE nativos, USB nativo, bastante RAM/Flash, 3,3 V.
- **Estratégia:** simulador → protoboard → perfboard → PCB própria. Um módulo por vez.
- Comparação de MCUs e justificativa: [docs/DECISOES-TECNICAS.md](docs/DECISOES-TECNICAS.md).

## Estrutura do repositório

- [`firmware/`](firmware/) — o **firmware integrado do dispositivo** (PlatformIO, modular).
- [`experimentos/`](experimentos/) — cada experimento isolado (`sketch.ino` + `diagram.json`).
- [`docs/`](docs/) — diário de bordo, decisões técnicas, relatórios.

## Firmware integrado

Um firmware único e modular, com arquitetura em camadas (**drivers → serviços → apps → menu**).
Cada app pluga pela mesma interface, então adicionar um não mexe nos outros.

| App | O que faz |
|---|---|
| Sobre | contador de boots, RAM livre, uptime |
| LED (PWM) | LED respirando |
| Buzzer | toca Do-Ré-Mi-Fá-Sol |
| WiFi Scan | redes ao redor (SSID/canal/RSSI) |
| Config | ajusta o brilho, salvo na NVS |
| IR / RFID / Sub-GHz / BLE | stubs, aguardando hardware |

Compilar com o [PlatformIO](https://platformio.org):

```bash
cd firmware
pio run
```

O binário sai em `firmware/.pio/build/esp32-s3/firmware.bin`. O projeto também traz um
`diagram.json` + `wokwi.toml` para rodar na extensão Wokwi do VS Code.

## Experimentos

| # | Experimento | O que ensina |
|---|---|---|
| 01 | Blink | saída GPIO, LED + resistor |
| 02 | PWM | duty cycle, brilho |
| 03 | Buzzer | PWM → som (frequência = nota) |
| 04 | Botões | INPUT_PULLUP, debounce |
| 05 | ADC | leitura analógica 12 bits |
| 06 | OLED | display I2C (U8g2), framebuffer |
| 07 | Menu | UI navegável, máquina de estados |
| 08 | NVS | config persistente na flash |
| 09 | WiFi Scanner | scan de redes (metadados) |
| 10 | WiFi + HTTP | conectar + HTTP GET |

Cada pasta tem um `sketch.ino` + `diagram.json` para colar no Wokwi (06 e 07 precisam da
biblioteca **U8g2**). Demo do menu ao vivo: https://wokwi.com/projects/477429861464182785

## Roadmap

Eletrônica → MCU → display/UI → armazenamento → comunicação → módulos → firmware completo → PCB →
dispositivo portátil → V2/V3.
