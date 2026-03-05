#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// --- Configuració Pins TTGO T-Beam ---
#define SCK      5
#define MISO     19
#define MOSI     27
#define SS       18
#define RST      23
#define DIO0     26

// --- Pins dels sensors ---
#define PIN_POT     35  
#define PIN_PH      33  
#define LED_AZUL     4   

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_AZUL, OUTPUT);
  digitalWrite(LED_AZUL, LOW);

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(868E6)) {
    Serial.println("Error LoRa");
    while (1);
  }
  
  analogReadResolution(12);
  Serial.println("--- EMISSOR CICLE ESTRICTE: POT -> PH -> POT -> PH ---");
}

void loop() {
  
  // ==========================================
  // 1. ENVIAR POTENCIÒMETRE
  // ==========================================
  int adcPot = analogRead(PIN_POT);
  float vPot = adcPot * (3.3 / 4095.0);

  digitalWrite(LED_AZUL, HIGH);
  LoRa.beginPacket();
  LoRa.print("POT:");
  LoRa.print(vPot, 2);
  LoRa.endPacket();
  digitalWrite(LED_AZUL, LOW);
  
  Serial.print("1. Enviat POT: "); Serial.println(vPot, 2);

  // ESPERA ESTRICTA DE 2 SEGONS
  delay(2000);

  // ==========================================
  // 2. ENVIAR pH
  // ==========================================
  int adcPH = analogRead(PIN_PH);
  float vPH = adcPH * (3.3 / 4095.0);
  float valorPH = 7.0 + ((1.65 - vPH) * 3.5);

  digitalWrite(LED_AZUL, HIGH);
  LoRa.beginPacket();
  LoRa.print("PH:");
  LoRa.print(valorPH, 2);
  LoRa.endPacket();
  digitalWrite(LED_AZUL, LOW);

  Serial.print("2. Enviat PH: "); Serial.println(valorPH, 2);

  // ESPERA ESTRICTA DE 5 SEGONS ABANS DEL SEGÜENT POT
  delay(5000);
  
  // Al final del loop, el codi torna a dalt de tot i envia el POT
}
