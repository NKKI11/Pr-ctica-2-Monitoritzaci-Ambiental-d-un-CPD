// ===================================================
// Pràctica 2 - Versió 3: COMPLETA
// Tots els sensors + alertes + comandes
// ===================================================

const int pinLED = 2;
const int pinLDR = 34;
const int pinLM35 = 35;
const float TEMP_LLINDAR = 25.0;
const int LLUM_LLINDAR = 500;
bool alertaActiva = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(pinLED, OUTPUT);
  pinMode(pinLDR, INPUT);
  pinMode(pinLM35, INPUT);
  
  Serial.println("=== SISTEMA DE MONITORITZACIÓ CPD ===");
  Serial.println("Comandes disponibles:");
  Serial.println("  STATUS    -> Mostra temperatura i llum actuals");
  Serial.println("  LED_OFF   -> Apaga manualment el LED d'alerta");
  Serial.println("======================================");
  Serial.println();
}

float llegirTemperatura() {
  int valorAnalogic = analogRead(pinLM35);
  float voltatge = valorAnalogic * (3.3 / 4095.0);
  float temperatura = voltatge / 0.01;
  return temperatura;
}

int llegirLlum() {
  return analogRead(pinLDR);
}

void processarComanda(String comanda) {
  comanda.trim();

  if (comanda.equalsIgnoreCase("STATUS")) {
    float temp = llegirTemperatura();
    int llum = llegirLlum();
    Serial.println("--- ESTAT ACTUAL ---");
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");
    Serial.print("Nivell de llum: ");
    Serial.println(llum);
    Serial.println("--------------------");

  } else if (comanda.equalsIgnoreCase("LED_OFF")) {
    digitalWrite(pinLED, LOW);
    alertaActiva = false;
    Serial.println("LED apagat manualment.");

  } else if (comanda.length() > 0) {
    Serial.println("Comanda no reconeguda. Utilitza STATUS o LED_OFF.");
  }
}

void loop() {
  float temperatura = llegirTemperatura();
  int llum = llegirLlum();

  // Alertes
  if (temperatura > TEMP_LLINDAR) {
    digitalWrite(pinLED, HIGH);
    alertaActiva = true;
    Serial.println("!!! ALERTA: Sobreescalfament CPD !!!");
  }
  else if (llum > LLUM_LLINDAR) {
    digitalWrite(pinLED, HIGH);
    alertaActiva = true;
    Serial.println("!!! AVÍS: Porta oberta o llum encesa !!!");
  }
  else {
    if (alertaActiva) {
        digitalWrite(pinLED, LOW);
        alertaActiva = false;
    }
  }

  // Mostrar cada 2 segons
  static unsigned long tempsAnterior = 0;
  unsigned long tempsActual = millis();

  if (tempsActual - tempsAnterior >= 2000) {
    tempsAnterior = tempsActual;
    Serial.print("[Lectura] Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C, Llum: ");
    Serial.println(llum);
  }

  // Comandes Serial
  if (Serial.available() > 0) {
    String comandaRebuda = Serial.readStringUntil('\n');
    processarComanda(comandaRebuda);
  }

  delay(100);
}