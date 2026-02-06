#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define SCK     5
#define MISO    19
#define MOSI    27
#define SS      18
#define RST     23
#define DIO0    26
#define PIN_ANALOGIC 21 

// --- CAMBIA ESTO SEGÚN LA PLACA ---
bool esEmissor = true; 
// ----------------------------------

void setup() {
  Serial.begin(115200);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(868E6)) {
    Serial.println("Error en iniciar LoRa!");
    while (1);
  }
  Serial.println(esEmissor ? "Modo EMISOR listo" : "Modo RECEPTOR listo");
}

void loop() {
  if (esEmissor) {
    int valor = analogRead(PIN_ANALOGIC);
    LoRa.beginPacket();
    LoRa.print("valor: ");
    LoRa.print(valor);
    LoRa.endPacket();
    
    Serial.print("Enviado: ");
    Serial.println(valor);
    delay(2000); 
  } else {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      Serial.print("Recibido: ");
      while (LoRa.available()) {
        Serial.print((char)LoRa.read());
      }
      Serial.println();
    }
  }
}