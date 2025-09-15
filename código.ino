/*
  Projeto: Registro e Validação de QR Code para Peneira de Futebol
  Descrição:
  
Participante se cadastra no site -> gera QR Code com ID único.
No dia, ESP32 lê o QR (simulado via Serial no Wokwi).
ESP32 verifica em lista interna de códigos válidos.
Se válido -> confirma presença (LED verde).
Se inválido -> acesso negado (LED vermelho).
*/

int ledVerde = 2;    // LED onboard do ESP32 (acesso permitido)
int ledVermelho = 4; // LED externo para acesso negado

// Lista simulada de códigos válidos
String codigosValidos[] = {
  "PENEIRA2025A",
  "PENEIRA2025B",
  "PENEIRA2025C",
  "JOGADOR123",
  "ENTRADA45"
};
int totalCodigos = 5;

void setup() {
  Serial.begin(115200);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  Serial.println("Digite o código do QR (simulação no Wokwi):");
  Serial.println("Códigos válidos de exemplo:");
  for (int i = 0; i < totalCodigos; i++) {
    Serial.println(" - " + codigosValidos[i]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String qrData = Serial.readStringUntil('\n');
    qrData.trim();

    Serial.print("QR lido: ");
    Serial.println(qrData);

    if (verificarCodigo(qrData)) {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
      Serial.println(" Acesso liberado! Presença confirmada.");
    } else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);
      Serial.println(" Código inválido! Acesso negado.");
    }
  }
}

// Função para verificar se o código está na lista
bool verificarCodigo(String codigo) {
  for (int i = 0; i < totalCodigos; i++) {
    if (codigosValidos[i] == codigo) {
      return true;
    }
  }
  return false;
} 
