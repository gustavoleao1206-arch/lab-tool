// ============================================================================
// Experimento 04 - Botoes + debounce
// Nivel 2 | ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x | sem bibliotecas
//
// Le 3 botoes (CIMA=5, BAIXO=6, OK=7) com pull-up interno (INPUT_PULLUP) e
// debounce por tempo, avisando no Serial apenas UMA vez por aperto.
//
// Conceitos: pull-up (pino em HIGH quando solto; LOW quando apertado -> GND),
// bouncing mecanico (contatos "tremem" por ms), debounce (so aceita a leitura
// depois que fica estavel), e borda de descida (HIGH->LOW = o aperto).
//
// Nota: DEBOUNCE_MS = 40 e o valor correto p/ hardware real. No simulador em
// segundo plano (que roda lento), usamos 1 ms para captar o clique sintetico.
// ============================================================================

const int QTD = 3;
const int pinos[QTD]   = {5, 6, 7};
const char* nomes[QTD] = {"CIMA", "BAIXO", "OK"};

const unsigned long DEBOUNCE_MS = 40;   // hardware real: 40; sim headless: 1

int estavel[QTD];
int ultima[QTD];
unsigned long tMud[QTD];

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("Experimento 04 - Botoes + debounce");
  Serial.println("Aperte CIMA(5), BAIXO(6) ou OK(7).");
  for (int i = 0; i < QTD; i++) {
    pinMode(pinos[i], INPUT_PULLUP);
    int l = digitalRead(pinos[i]);
    estavel[i] = l; ultima[i] = l; tMud[i] = millis();
  }
}

void loop() {
  unsigned long agora = millis();
  for (int i = 0; i < QTD; i++) {
    int l = digitalRead(pinos[i]);
    if (l != ultima[i]) { ultima[i] = l; tMud[i] = agora; }      // reinicia relogio
    if ((agora - tMud[i]) >= DEBOUNCE_MS) {                      // leitura estavel?
      if (l != estavel[i]) {
        estavel[i] = l;
        if (estavel[i] == LOW) {                                // borda = aperto
          Serial.print("Botao pressionado: ");
          Serial.println(nomes[i]);
        }
      }
    }
  }
}
