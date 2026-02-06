#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// Definiciones de pines para TTGO T-Beam
#define SCK     5
#define MISO    19
#define MOSI    27
#define SS      18
#define RST     23
#define DIO0    26

#define PIN_ANALOGIC 35  // Pin de lectura (ADC1)
#define LED_AZUL     4   

// Cambia a 'false' en la otra placa para que actúe como receptor
bool esEmissor = true; 

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_AZUL, OUTPUT);
  digitalWrite(LED_AZUL, LOW);

  // Inicializar SPI con los pines específicos de la T-Beam
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  // Inicializar frecuencia LoRa (868MHz para Europa)
  if (!LoRa.begin(868E6)) {
    Serial.println("Error al iniciar LoRa. Revisa las conexiones.");
    while (1);
  }
  
  // Configuración del ADC a 12 bits (0 - 4095)
  analogReadResolution(12);
  
  Serial.println(esEmissor ? "--- MODO EMISOR ACTIVO ---" : "--- MODO RECEPTOR ACTIVO ---");
}

void loop() {
  if (esEmissor) {
    // 1. Leer el valor analógico
    int valorADC = analogRead(PIN_ANALOGIC);

    // 2. Convertir a voltios (Fórmula: Lectura * (Voltaje Max / Resolución Max))
    // Usamos 4095.0 para forzar el cálculo en decimales (float)
    float voltios = valorADC * (3.3 / 4095.0);

    // Indicador visual de envío
    digitalWrite(LED_AZUL, HIGH); 
    
    // 3. Enviar el valor de voltios por LoRa
    LoRa.beginPacket();
    LoRa.print(voltios, 2); // Enviamos el número con 2 decimales
    LoRa.endPacket();
    
    digitalWrite(LED_AZUL, LOW);

    // Monitorización local
    Serial.print("Lectura ADC: ");
    Serial.print(valorADC);
    Serial.print(" | Voltaje enviado: ");
    Serial.print(voltios);
    Serial.println(" V");

    delay(2000); 
  } else {
    // Lógica del Receptor
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      digitalWrite(LED_AZUL, HIGH);
      
      Serial.print("Paquete recibido: ");
      while (LoRa.available()) {
        String data = LoRa.readString();
        Serial.print(data);
        Serial.println(" V");
      }
      
      digitalWrite(LED_AZUL, LOW);
    }
  }
}