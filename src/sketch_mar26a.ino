// Definición de pines
const int pinTemp = 2;   
const int pinLuz = 4;    
const int pinLED = 25;   

// Control de tiempo
unsigned long tiempoAnterior = 0;
const long intervalo = 500; // 0.5 segundos

void setup() {
  // Es vital que el monitor serie esté a 115200
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  pinMode(pinTemp, INPUT);
  pinMode(pinLuz, INPUT);
  
  Serial.println("--- MONITORIZACIÓN EN TIEMPO REAL (0.5s) ---");
  Serial.println("Los datos se actualizarán en la misma línea.");
  delay(1000);
}

void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    // 1. Lecturas
    int lecturaADC = analogRead(pinTemp);
    float voltaje = (lecturaADC * 3.3) / 4095.0;
    float temperatura = voltaje * 100.0; 
    int valorLuz = analogRead(pinLuz);

    // 2. Lógica del LED (17°C)
    if (temperatura >= 17.0) {
      digitalWrite(pinLED, HIGH);
    } else if (temperatura < 16.5) {
      digitalWrite(pinLED, LOW);
    }

    // 3. IMPRESIÓN EN LA MISMA LÍNEA
    // \r vuelve al inicio de la línea. 
    // Imprimimos espacios al final para limpiar caracteres antiguos si la cifra se acorta.
    Serial.print("\rTEMP: "); 
    Serial.print(temperatura, 2); 
    Serial.print(" °C | LLUM: "); 
    Serial.print(valorLuz);
    Serial.print(" | LED: ");
    Serial.print(digitalRead(pinLED) ? "ON " : "OFF");
    
    // Alerta rápida de intrusión al lado
    if (valorLuz > 500) {
      Serial.print(" | [!] INTRUSIÓ DETECTADA");
    } else {
      Serial.print(" | [OK] RACK TANCAT      ");
    }
  }

  // Control Manual (LED_OFF / STATUS)
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "LED_OFF") {
      digitalWrite(pinLED, LOW);
      Serial.println("\n>> LED apagat manualment."); // Salto de línea para no romper el monitor
    }
  }
}
