# Relatório — Firmware-base e Nível 5 (simulador Wokwi)

**Placa:** ESP32-S3 · **Ambiente:** Wokwi (Arduino-ESP32)

## Resumo

Os fundamentos de software do dispositivo foram construídos e **validados no Wokwi** — do Nível 1
ao 5: eletrônica básica, GPIO/I-O, display + interface, armazenamento e WiFi. São 10 experimentos,
cada um com código comentado e circuito.

Escopo de segurança: tudo em equipamento próprio/autorizado; sem jamming, clonagem de credenciais
de terceiros ou interceptação; dual-use apenas na versão segura de laboratório.

## Onde o projeto vive

- **Firmware integrado:** [`firmware/`](../firmware/) (projeto PlatformIO, modular).
- **Experimentos:** [`experimentos/`](../experimentos/) — colar `sketch.ino` + `diagram.json` no Wokwi
  (06 e 07 precisam da lib U8g2).
- **Demo ao vivo (menu):** https://wokwi.com/projects/477429861464182785

## Os 10 experimentos

| # | Experimento | O que ensina | Prova | Status |
|---|---|---|---|---|
| 01 | Blink | GPIO como saída; LED+resistor; Lei de Ohm | LED pisca; serial `LED: ON/OFF` | ✅ |
| 02 | PWM | duty cycle = brilho; LEDC | LED "respira" | ✅ |
| 03 | Buzzer | PWM, frequência = **nota**; `ledcWriteTone` | som + serial `Nota: Do (262 Hz)` | ✅ |
| 04 | Botões | `INPUT_PULLUP`, bouncing, **debounce** | serial `Botao pressionado: OK` | ✅ |
| 05 | ADC | leitura analógica 12 bits (0..4095) | serial `Bruto: 2050 \| 50.1% \| 1.65 V` | ✅ |
| 06 | OLED | display I2C (U8g2), framebuffer | tela `Lab-Tool / Contador: 5` | ✅ |
| 07 | Menu | UI navegável + máquina de estados | menu `IR / RFID / Sub-GHz / Config / Sobre` | ✅ |
| 08 | NVS | config persistente na flash (Preferences) | serial `Boot numero 1 / Brilho: 128` | ✅ |
| 09 | WiFi Scanner | scan de redes (SSID/canal/RSSI/segurança) | serial `1) Wokwi-GUEST  ch:6  seg:0` | ✅ |
| 10 | WiFi + HTTP | conectar + requisição HTTP GET | serial `IP 10.10.0.2` / `GET -> 200` | ✅ |

### Mapa de pinos

| Função | Pino | Função | Pino |
|---|---|---|---|
| LED | GPIO2 | Botão CIMA | GPIO5 |
| Buzzer | GPIO4 | Botão BAIXO | GPIO6 |
| Potenciômetro (SIG) | GPIO1 (ADC1) | Botão OK | GPIO7 |
| OLED SDA | GPIO8 | OLED SCL | GPIO9 |

### O "porquê" que conecta tudo

- **01 → 02 → 03** são a mesma técnica (PWM) evoluindo: ligar/desligar → proporção (brilho) →
  frequência audível (nota). Essa frequência vira, no Nível 6, a portadora de 38 kHz do infravermelho.
- **04 + 05 + 06** são as entradas/saídas do dispositivo: botão (digital), potenciômetro (analógico),
  display (saída visual).
- **07 (Menu)** junta tudo numa UI com a regra de ouro: `ler entrada → atualizar estado → desenhar`.
- **08 (NVS)** guarda config que sobrevive ao desligar; **09/10** cobrem o WiFi.

## Limitações do simulador

- A simulação em segundo plano roda devagar; em testes de botão foi preciso reduzir o debounce
  para captar o clique (o valor real está nos arquivos).
- O Wokwi **não simula Bluetooth/BLE** nem comunicação entre dois dispositivos (ESP-NOW) — essas
  partes ficam para o hardware real.
- O editor do Wokwi às vezes junta o primeiro `#include` com a linha seguinte e autocompleta
  `<WiFi.h>` para `<WiFiNINA.h>` — conferir após colar.

## Próximos passos

1. **Hardware físico:** montar os experimentos 01–10 na protoboard.
2. **Nível 6 — Módulos:** IR (replay do próprio controle), RFID (ler/gravar tags próprias),
   Sub-GHz CC1101 (RX-first, respeitando a regulamentação local).
3. Firmware integrado (Nível 7) → PCB (Nível 8) → portátil com bateria (Nível 9).
