# Experimento 02 — PWM (controlar o brilho de um LED)

**Nível:** 1/2 · **Ambiente:** Wokwi · **Placa:** ESP32-S3 (core Arduino-ESP32 3.x)

## Objetivo
Fazer o LED "respirar" — brilho subindo de 0 a 100% e voltando — em vez de só ligar/desligar.

## Conceito: PWM (Pulse Width Modulation)
Um pino digital só faz HIGH (3,3 V) ou LOW (0 V); não faz "meio brilho". O truque é
**ligar/desligar muito rápido** e controlar a **fração do tempo ligado** (o *duty cycle*).
O LED responde à média → mais tempo ligado = mais brilho.

Três parâmetros:
- **Duty cycle:** fração em HIGH; controla o brilho. Com 8 bits → `0` (0%) a `255` (100%).
- **Frequência:** quantos ciclos/segundo (5000 Hz aqui; rápido para o olho não ver piscar).
- **Resolução:** quantos degraus de brilho (8 bits = 256 níveis).

No ESP32 o hardware **LEDC** cuida disso:
- `ledcAttach(pino, freq, resolucao)` → configura o PWM (1× no `setup`).
- `ledcWrite(pino, duty)` → define o brilho (0..255).

> Circuito **idêntico** ao do Blink (GPIO2 → resistor 220 Ω → LED → GND).
> Só o software mudou — capacidade nova sem hardware novo.

## Como rodar no Wokwi
1. https://wokwi.com → **New Project** → **ESP32-S3** (ou reaproveite o projeto do Blink).
2. Cole `sketch.ino` na aba de código.
3. Cole `diagram.json` na aba correspondente (é o mesmo circuito do Blink).
4. ▶ play.

## Critério de sucesso
- O LED **acende suave e apaga suave** (efeito respiração), repetindo.
- No Serial Monitor alternam `Aumentando o brilho: 0 -> 100%` / `Diminuindo o brilho: 100% -> 0`.

## Desafios (mexa e observe)
1. Troque o `delay(8)` por `delay(2)` — a respiração fica mais rápida ou mais lenta?
2. Faça o LED ficar num brilho fixo de ~25%: no `setup`, depois do `ledcAttach`, chame
   `ledcWrite(LED_PIN, 64);` e comente todo o conteúdo do `loop`. (64 ≈ 25% de 255.)
3. Baixe `PWM_FREQ` para `5` (5 Hz) e aumente `delay` — agora você **vê** o piscar do PWM.
   Isso prova por que a frequência precisa ser alta para o brilho parecer contínuo.
