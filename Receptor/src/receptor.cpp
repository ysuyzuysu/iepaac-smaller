#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SSD1306Wire.h>

// Pins Pantalla
#define OLED_SDA 21
#define OLED_SCL 22
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

// Pin de lectura de Bateria
#define BATT_PIN 35

// Pins LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

const char* ssid = "Aula 23";
const char* password = "223AuLa23";
const char* mqtt_server = "192.168.223.50";

WiFiClient espClient;
PubSubClient client(espClient);

String obtenirPercentatgeBateria() {
  int rawValue = analogRead(BATT_PIN);
  float voltage = (rawValue / 4095.0) * 3.3 * 2.0;
  int percent = map(voltage * 100, 320, 420, 0, 100);
  if (percent > 100) percent = 100;
  if (percent < 0) percent = 0;
  return String(percent) + "%";
}

void actualitzarPantalla(String linia1, String linia2) {
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 0, obtenirPercentatgeBateria());
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 15, linia1);
  display.drawString(0, 35, linia2);
  display.display();
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("TBeam_Receptor_ADO")) break;
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BATT_PIN, INPUT);
  display.init();
  display.flipScreenVertically();
  actualitzarPantalla("Iniciant...", "Espereu...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  client.setServer(mqtt_server, 1883);

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  LoRa.begin(868E6);
  actualitzarPantalla("LORA: OK", "Escoltant...");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    while (LoRa.available()) { message += (char)LoRa.read(); }

    String topic = "";
    String valor = "";

    // LÒGICA DE SEPARACIÓ (Parsing)
    if (message.startsWith("PH:")) {
      topic = "ado/ph";
      valor = message.substring(3);
    } 
    else if (message.startsWith("POT:")) {
      topic = "ado/pot";
      valor = message.substring(4);
    }
    else if (message.startsWith("TEMP:")) {
      topic = "ado/TEMP";
      valor = message.substring(5);
    }
    else if (message.startsWith("HUM:")) {
      topic = "ado/HUM";
      valor = message.substring(4);
    }
    else {
      topic = "ado/altres";
      valor = message;
    }

    if (client.publish(topic.c_str(), valor.c_str())) {
      actualitzarPantalla(topic, valor);
    }
  }
}
