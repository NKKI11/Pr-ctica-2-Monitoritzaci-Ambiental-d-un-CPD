// ===================================================
// Pràctica 2 - Versió 2: LDR + LM35
// ===================================================

const int pinLDR = 34;
const int pinLM35 = 35;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(pinLDR, INPUT);
  pinMode(pinLM35, INPUT);
  
  Serial.println("=== LECTURA SENSORS LDR i LM35 ===");
  Serial.println("Llegint dades cada 2 segons...");
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

void loop() {
  float temperatura = llegirTemperatura();
  int llum = llegirLlum();
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C | Llum: ");
  Serial.println(llum);
  
  delay(2000);
}
