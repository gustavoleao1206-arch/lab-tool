// ============================================================================
// Experimento 07 - Sistema de Menu (capstone da UI) - Nivel 3
// ESP32-S3 (Wokwi) | core 3.x | BIBLIOTECA NECESSARIA no Wokwi: "U8g2"
//
// OLED (SDA=8,SCL=9) + 3 botoes (CIMA=5, BAIXO=6, OK=7). Menu navegavel:
// CIMA/BAIXO movem a selecao, OK abre o item e volta.
//
// Base de firmware NAO-monolitico: o loop faz sempre 3 passos na ordem
//   lerBotoes() -> logica() -> desenha()
// (ler entrada -> atualizar estado -> mostrar saida). Cada funcao tem UMA
// responsabilidade; trocar o display ou somar botoes nao bagunca a logica.
//
// Nota: DB (debounce) = 25 ms e adequado p/ hardware/uso real. No simulador
// em segundo plano (roda lento) pode ser preciso reduzir p/ 1 ms captar o
// clique sintetico; com o mouse real em primeiro plano, 25 ms funciona.
// ============================================================================

#include <Wire.h>
#include <U8g2lib.h>

#define PINO_CIMA   5
#define PINO_BAIXO  6
#define PINO_OK     7

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 9, 8);

const char* itens[] = {"IR", "RFID", "Sub-GHz", "Config", "Sobre"};
const int   N = 5;
int sel = 0;

enum Estado { MENU, ITEM };
Estado estado = MENU;

const unsigned long DB = 25;   // debounce (ms)

struct Botao { uint8_t pino; int ant; int est; unsigned long t; bool borda; };
Botao bC = {PINO_CIMA,  HIGH, HIGH, 0, false};
Botao bB = {PINO_BAIXO, HIGH, HIGH, 0, false};
Botao bO = {PINO_OK,    HIGH, HIGH, 0, false};

void atB(Botao &b) {
  b.borda = false;
  int l = digitalRead(b.pino);
  if (l != b.ant) { b.t = millis(); b.ant = l; }
  if (millis() - b.t > DB) {
    if (l != b.est) { b.est = l; if (b.est == LOW) b.borda = true; }
  }
}
void lerBotoes() { atB(bC); atB(bB); atB(bO); }   // 1) ENTRADA

void desenhaMenu() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 8, "MENU");
  u8g2.drawHLine(0, 11, 128);
  for (int i = 0; i < N; i++) {
    int y = 22 + i * 10;
    if (i == sel) {                               // item selecionado = barra invertida
      u8g2.drawBox(0, y - 8, 128, 10);
      u8g2.setDrawColor(0); u8g2.drawStr(3, y, itens[i]); u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(3, y, itens[i]);
    }
  }
  u8g2.sendBuffer();
}
void desenhaItem() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13_tr);
  u8g2.drawStr(0, 16, itens[sel]);
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 40, "pressione OK");
  u8g2.drawStr(0, 52, "para voltar");
  u8g2.sendBuffer();
}
void desenha() { if (estado == MENU) desenhaMenu(); else desenhaItem(); }  // 3) SAIDA

void logica() {                                   // 2) LOGICA (maquina de estados)
  if (estado == MENU) {
    if (bC.borda) { sel--; if (sel < 0) sel = N - 1; Serial.print("Selecao: "); Serial.println(itens[sel]); }
    if (bB.borda) { sel++; if (sel >= N) sel = 0;    Serial.print("Selecao: "); Serial.println(itens[sel]); }
    if (bO.borda) { estado = ITEM; Serial.print("Entrou em: "); Serial.println(itens[sel]); }
  } else {
    if (bO.borda) { estado = MENU; Serial.println("Voltou ao menu"); }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_CIMA,  INPUT_PULLUP);
  pinMode(PINO_BAIXO, INPUT_PULLUP);
  pinMode(PINO_OK,    INPUT_PULLUP);
  u8g2.begin();
  Serial.println("Menu pronto. CIMA/BAIXO navega, OK abre.");
}

void loop() {
  lerBotoes();
  logica();
  desenha();
}
