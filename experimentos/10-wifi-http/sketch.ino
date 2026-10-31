// ============================================================================
// Experimento 10 - WiFi conectar + HTTP - Nivel 5
// ESP32-S3 (Wokwi) | core Arduino-ESP32 3.x | WiFi.h + HTTPClient.h (nativas)
//
// Conecta na rede virtual aberta "Wokwi-GUEST" (canal 6) e faz uma requisicao
// HTTP GET a um site publico de exemplo, imprimindo o codigo de status e o
// inicio da resposta. No Wokwi o acesso a internet passa por um GATEWAY
// (IP do ESP32 = 10.10.0.2). No HARDWARE real, troque por a SUA rede WiFi.
//
// Escopo seguro: conexao a uma rede de teste aberta + GET a um site publico.
//
// Conceitos:
//  - Modo estacao (STA): o ESP32 e cliente de um Access Point.
//  - WiFi.begin(ssid, senha, canal): informar o canal (6) pula a fase de scan
//    e conecta ~4s mais rapido no Wokwi.
//  - WiFi.status() == WL_CONNECTED indica conexao estabelecida.
//  - HTTPClient: begin(url) -> GET() (retorna o codigo HTTP; 200 = OK) ->
//    getString() (corpo) -> end().
//  - O gateway do Wokwi suporta TCP/UDP (nao suporta ping/ICMP).
//
// GOTCHA do editor Wokwi: ao digitar "#include <WiFi.h>" o autocomplete pode
// trocar por "<WiFiNINA.h>" (placa errada). Digite o include e aperte Esc
// ANTES do Enter para dispensar o autocomplete.
// ============================================================================

#include <WiFi.h>
#include <HTTPClient.h>

const char* SSID_REDE = "Wokwi-GUEST";   // rede aberta do simulador (senha vazia)

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("Experimento 10 - WiFi conectar + HTTP");

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_REDE, "", 6);          // "" = sem senha; 6 = canal (conecta mais rapido)
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;
  http.begin("http://example.com/");
  int codigo = http.GET();
  Serial.printf("HTTP GET -> codigo: %d\n", codigo);   // 200 = OK
  if (codigo > 0) {
    String corpo = http.getString();
    Serial.printf("Tamanho da resposta: %d bytes\n", corpo.length());
    Serial.println("Primeiros 150 caracteres:");
    Serial.println(corpo.substring(0, 150));
  }
  http.end();
}

void loop() {
  delay(5000);
}
