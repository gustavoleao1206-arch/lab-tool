# Experimento 01 — Blink (piscar um LED)

**Nível:** 1 (Eletrônica básica) · **Ambiente:** Wokwi (simulador) · **Placa:** ESP32-S3

## Objetivo
Fazer um LED piscar (0,5 s aceso / 0,5 s apagado) controlado por um pino do ESP32-S3.
É o "Olá, mundo" do hardware: a prova de que seu código controla o mundo físico.

## Conceitos
- **GPIO** (General Purpose Input/Output): pino que o programa liga/desliga.
- **Saída digital:** o pino assume dois níveis — `HIGH` (~3,3 V) ou `LOW` (0 V).
- **Resistor limitador:** sem ele, passa corrente demais e o LED (no mundo real) queima.
  Lei de Ohm: `I = (3,3 V − ~2 V do LED) / 220 Ω ≈ 6 mA` (seguro).
- **Programa Arduino:** `setup()` roda 1 vez; `loop()` repete para sempre.

## Circuito (pinagem)
| De | Para | Fio |
|---|---|---|
| ESP32 **GPIO2** | Resistor pino 1 | verde |
| Resistor pino 2 | LED ânodo (A) | verde |
| LED catodo (C) | ESP32 **GND** | preto |

> Por que GPIO2? É um pino de uso geral, seguro no ESP32-S3 (não é pino de "boot"/strapping).
> O mapa completo de pinos e quais evitar entra no Nível 2.

## Como rodar no Wokwi
1. Acesse https://wokwi.com → **New Project** → escolha **ESP32-S3**.
2. Cole o conteúdo de `sketch.ino` na aba de código (`sketch.ino` / `.cpp`).
3. Clique na aba **diagram.json** e cole o conteúdo de `diagram.json` deste experimento.
4. Clique no ▶ (play) para iniciar a simulação.

## Critério de sucesso
- O LED pisca 1×/segundo (0,5 s aceso / 0,5 s apagado).
- No **Serial Monitor** (embaixo) aparece `LED: ON` / `LED: OFF` alternando.

## Desafios (mexa e observe — depois me conte o que achou)
1. Troque os dois `delay(500)` por `delay(100)`. O que muda no piscar?
2. Faça o LED ficar 100 ms aceso e 900 ms apagado (piscada curta). Quais delays mudam?
3. No `diagram.json`, troque `"color": "red"` por `"green"`.
