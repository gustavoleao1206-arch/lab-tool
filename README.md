# Lab-Tool

> 🇬🇧 **English** · [🇧🇷 Português](README.pt-BR.md)

A DIY portable lab multi-tool, conceptually inspired by the Flipper Zero, built **from scratch**
on an **ESP32-S3** as a hands-on way to learn electronics, embedded systems, firmware, RF and
digital protocols.

> ⚠️ **Educational use only.** Everything here is meant to be tested on **your own equipment or
> with explicit authorization**. No jamming, no cloning of third-party credentials, no intrusion
> or interception. Dual-use topics are studied only in their safe, lab-side form, respecting local
> radio regulations.

## Status

- **Levels 1–4 (firmware foundations)** validated in the [Wokwi](https://wokwi.com) simulator:
  GPIO, PWM, buzzer, buttons + debounce, ADC, OLED display, a navigable menu, persistent config (NVS).
- **Level 5 (WiFi)** validated in the simulator: network scan + connect + HTTP request.
- **Level 7 (integrated firmware):** the experiments are unified into a single modular firmware
  (PlatformIO) that builds for the ESP32-S3.
- **Next:** physical hardware → radio modules (IR, RFID, Sub-GHz) → custom PCB → portable build.

## Architecture (V1)

- **MCU:** ESP32-S3 (ESP32-S3-DevKitC-1) — native WiFi/BLE, native USB, generous RAM/Flash, 3.3 V.
- **Approach:** simulator → breadboard → perfboard → custom PCB. One module at a time.
- MCU comparison and rationale: [docs/DECISOES-TECNICAS.md](docs/DECISOES-TECNICAS.md).

## Repository layout

- [`firmware/`](firmware/) — the **integrated device firmware** (PlatformIO, modular).
- [`experimentos/`](experimentos/) — each experiment in isolation (`sketch.ino` + `diagram.json`).
- [`docs/`](docs/) — development log, technical decisions, reports.

## Integrated firmware

A single, modular firmware with a layered architecture (**drivers → services → apps → menu**).
Each app plugs in through the same interface, so adding one doesn't touch the others.

| App | What it does |
|---|---|
| About | boot count, free RAM, uptime |
| LED (PWM) | breathing LED |
| Buzzer | plays Do-Re-Mi-Fa-Sol |
| WiFi Scan | nearby networks (SSID/channel/RSSI) |
| Config | adjusts brightness, saved to NVS |
| IR / RFID / Sub-GHz / BLE | stubs, waiting for hardware |

Build it with [PlatformIO](https://platformio.org):

```bash
cd firmware
pio run
```

The binary lands in `firmware/.pio/build/esp32-s3/firmware.bin`. The project also ships a
`diagram.json` + `wokwi.toml` to run it in the Wokwi VS Code extension.

## Experiments

| # | Experiment | Teaches |
|---|---|---|
| 01 | Blink | GPIO output, LED + resistor |
| 02 | PWM | duty cycle, brightness |
| 03 | Buzzer | PWM → sound (frequency = note) |
| 04 | Buttons | INPUT_PULLUP, debounce |
| 05 | ADC | 12-bit analog read |
| 06 | OLED | I2C display (U8g2), framebuffer |
| 07 | Menu | navigable UI, state machine |
| 08 | NVS | persistent config in flash |
| 09 | WiFi Scanner | scan networks (metadata) |
| 10 | WiFi + HTTP | connect + HTTP GET |

Each folder has a `sketch.ino` + `diagram.json` you can paste into Wokwi (06 and 07 need the
**U8g2** library). Live menu demo: https://wokwi.com/projects/477429861464182785

## Roadmap

Electronics → MCU → display/UI → storage → communication → modules → full firmware → PCB →
portable device → V2/V3.
