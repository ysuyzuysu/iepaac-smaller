#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <SSD1306Wire.h> 
#include "DHT.h"

// --- Configuració Pantalla OLED ---
#define OLED_SDA 21
#define OLED_SCL 22
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL); 

// --- Configuració DHT11 ---
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- Pins LoRa TTGO T-Beam ---
#define SCK      5
#define MISO     19
#define MOSI     27
#define SS       18
#define RST      23
#define DIO0     26

// --- Pins Sensors ---
#define PIN_POT     35  
#define PIN_PH      32
#define LED_AZUL     4   

// --- DECLARACIÓ DE FUNCIONS (Prototips) ---
// Això li diu al compilador que aquestes funcions existeixen més a baix
void actualitzarPantalla(String linia1, String linia2);
void enviarLoRa(String mensaje);

void setup() {
    Serial.begin(115200);
    dht.begin();
    display.init();
    display.flipScreenVertically();
    actualitzarPantalla("EMISSOR ADO", "Iniciant...");

    pinMode(LED_AZUL, OUTPUT);

    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);
    if (!LoRa.begin(868E6)) {
        actualitzarPantalla("LORA ERROR", "Revisa pins");
        while (1);
    }
    
    analogReadResolution(12);
    actualitzarPantalla("LORA OK", "Esperant...");
    delay(1500);
}

void loop() {
    // 1. ENVIAR POT
    float vPot = analogRead(PIN_POT) * (3.3 / 4095.0); // Ajustat a 3.3V que és l'estàndard de la T-*Beam
    String msgPot = "POT:" + String(vPot, 2);
    enviarLoRa(msgPot);
    delay(2000);

    // 2. ENVIAR PH
    float vPH = analogRead(PIN_PH) * (3.3 / 4095.0);
    float valorPH = 7.0 + ((1.65 - vPH) * 3.5);
    String msgPH = "PH:" + String(valorPH, 2);
    enviarLoRa(msgPH);
    delay(2000);

    // 3. ENVIAR TEMPERATURA I HUMITAT
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Error leyendo el DHT11!");
        // No enviem res si falla la lectura
    } else {
        String msgT = "TEMP:" + String(t, 1);
        String msgH = "HUM:" + String(h, 0);
        enviarLoRa(msgT);
        delay(1000);
        enviarLoRa(msgH);
    }
    delay(5000);
}

// --- DEFINICIÓ DE FUNCIONS ---
void enviarLoRa(String mensaje) {
    actualitzarPantalla("ENVIANT...", mensaje);
    digitalWrite(LED_AZUL, HIGH);
    LoRa.beginPacket();
    LoRa.print(mensaje);
    LoRa.endPacket();
    digitalWrite(LED_AZUL, LOW);
    Serial.println("Enviat: " + mensaje);
}

void actualitzarPantalla(String linia1, String linia2) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 10, linia1);
    display.drawString(0, 30, linia2);
    display.display();
}
