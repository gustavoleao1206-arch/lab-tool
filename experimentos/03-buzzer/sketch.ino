// ============================================================================
// Experimento 03 - Buzzer (PWM virando som)
// Nivel 1/2 | Placa: ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x
//
// Ideia central: a MESMA tecnica do Exp 02 (PWM/LEDC). La a frequencia so
// precisava ser alta para o olho nao ver piscar; AQUI a FREQUENCIA e a NOTA.
// Buzzer no GPIO4. API do core 3.x: ledcAttach(pino,freq,res) + ledcWriteTone.
// Sem bibliotecas externas.
//
// Notas (Hz): Do=262 Re=294 Mi=330 Fa=349 Sol=392
// ============================================================================

const int PINO_BUZZER = 4;
const int RESOLUCAO   = 10;

const char* nomes[]       = {"Do","Re","Mi","Fa","Sol"};
const int   frequencias[] = {262, 294, 330, 349, 392};
const int   TOTAL_NOTAS   = 5;

void setup() {
  Serial.begin(115200);
  delay(300);
  ledcAttach(PINO_BUZZER, 1000, RESOLUCAO);  // prepara o PWM no pino (1x)
  Serial.println("Experimento 03 - Buzzer");
}

void loop() {
  for (int i = 0; i < TOTAL_NOTAS; i++) {
    ledcWriteTone(PINO_BUZZER, frequencias[i]);  // AQUI a frequencia = nota
    Serial.print("Nota: "); Serial.print(nomes[i]);
    Serial.print(" ("); Serial.print(frequencias[i]); Serial.println(" Hz)");
    delay(400);
    ledcWriteTone(PINO_BUZZER, 0);               // frequencia 0 = silencio
    delay(120);
  }
  Serial.println("--- fim, repetindo ---");
  delay(1000);
}
