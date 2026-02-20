#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// --- Configuración Pines TTGO T-Beam ---
#define SCK      5
#define MISO     19
#define MOSI     27
#define SS       18
#define RST      23
#define DIO0     26

// --- Pines de tus Sensores ---
#define PIN_POT  35  // Potenciómetro (Señal)
#define PIN_EC   3 // Sensor EC DFR0300-H (Cable Blanco)
#define LED_AZUL  4   

// --- Configuración de Calibración ---
#define VREF 3.3            // Voltaje de referencia de la placa
#define ADC_RES 4095.0      // Resolución 12 bits (ESP32)
#define K_CELL 10.0         // Constante de tu sonda

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_AZUL, OUTPUT);
  digitalWrite(LED_AZUL, LOW);

  // Inicializar comunicación SPI para LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  // Inicializar LoRa (Frecuencia 868MHz Europa)
  if (!LoRa.begin(868E6)) {
    Serial.println("Error: No se pudo iniciar LoRa. Revisa la antena.");
    while (1);
  }

  // Configurar resolución de lectura analógica
  analogReadResolution(12); 
  
  Serial.println("--- TRANSMISOR LISTO ---");
  Serial.println("Leyendo Potenciómetro (P35) y EC (P33)...");
}

void loop() {
  // 1. LEER DATOS CRUDOS
  int rawPot = analogRead(PIN_POT);
  int rawEC  = analogRead(PIN_EC);

  // 2. CONVERTIR A VOLTAJE
  float voltPot = rawPot * (VREF / ADC_RES);
  float voltEC  = rawEC  * (VREF / ADC_RES);

  // 3. CALCULAR CONDUCTIVIDAD
  // Para la placa DFR0300-H, el valor de EC es proporcional al voltaje
  float valorEC = voltEC * K_CELL; 

  // 4. MOSTRAR EN MONITOR SERIAL (Para depuración)
  Serial.print("POT: "); Serial.print(voltPot, 2); Serial.print("V | ");
  Serial.print("EC Raw: "); Serial.print(rawEC); 
  Serial.print(" | EC Calc: "); Serial.print(valorEC, 2); Serial.println(" ms/cm");

  // 5. ENVIAR POR LORA
  digitalWrite(LED_AZUL, HIGH); // Parpadeo al enviar
  
  LoRa.beginPacket();
  LoRa.print("P:");  LoRa.print(voltPot, 2);
  LoRa.print("|E:"); LoRa.print(valorEC, 2);
  LoRa.endPacket();
  
  digitalWrite(LED_AZUL, LOW);

  delay(2000); // Pausa de 2 segundos entre envíos
}
