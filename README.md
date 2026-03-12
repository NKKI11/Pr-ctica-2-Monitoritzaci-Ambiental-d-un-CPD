# Pràctica 2: Monitorització Ambiental d'un CPD

## 👋 Descripció General

Aquest projecte implementa un sistema de monitorització ambiental per a un Centre de Processament de Dades (CPD) utilitzant un ESP32. L'objectiu és simular un entorn industrial IoT on es vigilen condicions crítiques (temperatura i llum) per prevenir fallades i estalviar energia.

El sistema és capaç de:
- Llegir la temperatura ambient mitjançant un sensor **LM35**.
- Llegir el nivell de llum mitjançant una fotoresistència **LDR**.
- Activar automàticament un **LED d'alerta** (i missatges per Serial) quan es superen els llindars de seguretat.
- Permetre la interacció amb l'usuari a través de comandes enviades pel Monitor Sèrie.

## 🎯 Objectius de la Pràctica

1.  **Sensibilitzar l'ESP32:** Connectar sensors analògics per percebre el món real (temperatura i llum).
2.  **Automatització:** Crear un sistema d'alertes basat en llindars (programació reactiva).
3.  **Interactivitat:** Implementar un menú d'usuari per consultar dades i controlar actuadors (LED) via Serial.
4.  **Gestió de Projecte:** Aprendre a organitzar una pràctica dins d'un entorn professional utilitzant **GitHub Issues** i un **tauler Kanban**.

## 🛠️ Components Utilitzats

- **Microcontrolador:** ESP32 (amb ADC de 12 bits per llegir sensors analògics).
- **Sensor de Temperatura:** LM35 (sortida analògica lineal: 10mV/ºC).
- **Sensor de Llum:** LDR (Light Dependent Resistor) en configuració de divisor de tensió.
- **Actuador:** LED (per a l'alerta visual).
- **Resistències:** 10kΩ per al LDR, 220Ω per al LED.

## 🔌 Esquema de Connexions

*(Aquí has de posar la imatge del teu esquema de Fritzing)*

```plaintext
ESP32 GPIO 34  <-->  Sortida del divisor LDR (LDR + R 10kΩ a GND i 3.3V)
ESP32 GPIO 35  <-->  Pin Vout del sensor LM35
ESP32 GPIO 2   <-->  Resistència 220Ω --> Ànode del LED
ESP32 GND      <-->  Càtode LED, GND LM35, GND LDR
ESP32 3.3V     <-->  VCC LM35 i VCC LDR
