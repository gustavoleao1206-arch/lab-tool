# Lab-Tool — Firmware integrado (v0.1)

Firmware do dispositivo (ESP32-S3), que junta os experimentos num programa único,
modular e navegável por menu. Projeto **PlatformIO**.

## Arquitetura (camadas, dependência só para baixo)

```
main.cpp            boot + loop: ler botões -> menu/app -> desenhar
  └─ Menu           lista de apps + navegação + máquina de estados
       └─ App       interface comum (enter/loop/exit); o núcleo não conhece os apps
            └─ apps/ AppInfo, AppLed, AppBuzzer, AppWifiScan, AppSettings, AppStub(x4)
  serviços: Config (NVS), Logger
  drivers:  Display (U8g2), Buttons (debounce)
  base:     board_pins.h (mapa de pinos), pwm_compat.h (LEDC 2.x/3.x)
```

Trocar o display, somar um botão ou adicionar um app **não** mexe nas outras camadas.

## Apps

| App | O que faz | Estado |
|---|---|---|
| Sobre | boots, RAM livre, uptime | ✅ |
| LED (PWM) | LED respirando | ✅ |
| Buzzer | toca Do-Re-Mi-Fa-Sol | ✅ |
| WiFi Scan | redes ao redor (SSID/canal/RSSI) | ✅ |
| Config | ajusta brilho e salva na NVS | ✅ |
| IR / RFID / Sub-GHz / BLE | stubs "requer hardware" | ⏳ aguardando módulos |

## Compilar

```bash
cd firmware
pio run                 # ou: python -m platformio run
```

O binário sai em `.pio/build/esp32-s3/firmware.bin`.

O script `add_esp32s3_ld.py` (em `extra_scripts`) corrige dois detalhes do
`espressif32@8.0.0`: coloca os *linker scripts* do ESP32-S3 no caminho de busca
(senão o link falha com `cannot open linker script`) e remove a geração do
`firmware.map` (só diagnóstico).

### Windows com acento/espaço no caminho

Se o seu usuário tiver acento (ex.: `C:\Users\João\...`), o linker da toolchain
não consegue abrir caminhos não-ASCII dos pacotes. Compile fazendo o PlatformIO
enxergar tudo pelo caminho curto 8.3 (ASCII). No Git Bash:

```bash
export PLATFORMIO_CORE_DIR="$(cmd //c 'for %I in ("%USERPROFILE%\.platformio") do @echo %~sfI')"
cd "$(cmd //c 'for %I in (".") do @echo %~sfI')"
pio run
```

## Rodar

- **Hardware:** `pio run -t upload` com a placa conectada (porta USB).
- **Wokwi:** use a extensão *Wokwi for VS Code* — `diagram.json` e `wokwi.toml` já estão aqui
  (apontando para o binário buildado). Navegue com CIMA/BAIXO/OK.

## Pinos (ver `src/board_pins.h`)

LED=GPIO2 · Buzzer=GPIO4 · Botões CIMA/BAIXO/OK=GPIO5/6/7 · OLED I2C SDA=GPIO8 / SCL=GPIO9.
