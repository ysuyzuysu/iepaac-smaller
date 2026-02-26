#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SSD1306Wire.h> // Nova llibreria del teu company

// Configuració Pantalla OLED (Igual que el teu company)
#define OLED_SDA 21
#define OLED_SCL 22
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL); 

// Pins LoRa per a la TTGO T-Beam
#define SCK      5
#define MISO    19
#define MOSI    27
#define SS      18
#define RST     23
#define DIO0    26

// Configuració WiFi
const char* ssid = "Aula 23";
const char* password = "223AuLa23";

// Configuració MQTT
const char* mqtt_server = "192.168.223.50";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Nova funció d'actualitzar pantalla adaptada a la llibreria SSD1306Wire
void actualitzarPantalla(String linia1, String linia2) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, linia1);
  display.drawString(0, 30, linia2);
  display.display();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentant connexió MQTT...");
    actualitzarPantalla("MQTT:", "Connectant...");
    if (client.connect("TBeam_Receptor_ADO")) {
      Serial.println("Connectat!");
      actualitzarPantalla("MQTT:", "Connectat OK");
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // 0. Inicialitzar Pantalla OLED (Mètode del teu company)
  display.init();
  display.flipScreenVertically();
  actualitzarPantalla("Iniciant...", "Espereu...");

  // 1. Connectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi OK.");
  actualitzarPantalla("WiFi: Connectat", WiFi.localIP().toString());
  delay(2000);

  // 2. Configurar servidor MQTT
  client.setServer(mqtt_server, mqtt_port);

  // 3. Configurar LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Error LoRa!");
    actualitzarPantalla("LORA ERROR", "Revisa pins");
    while (1);
  }
  actualitzarPantalla("LORA: OK", "Escoltant...");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Escoltant ràdio LoRa
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    Serial.println("Rebut via LoRa: " + message);
    String topic = "";
    String valor = "";

    // SEPARACIÓ DE SUBTOPICS PER ETIQUETA
    if (message.startsWith("PH:")) {
      topic = "ado/ph";
      valor = message.substring(3); // Treu "PH:"
    } 
    else if (message.startsWith("POT:")) {
      topic = "ado/pot";
      valor = message.substring(4); // Treu "POT:"
    }
    else {
      topic = "ado/altres"; 
      valor = message;
    }

    // Publicar al topic decidit per la lògica anterior
    if (client.publish(topic.c_str(), valor.c_str())) {
      Serial.print("Dades publicades a: ");
      Serial.println(topic);
      
      actualitzarPantalla("Publicant dades...", topic);
      
      delay(1000); 
      actualitzarPantalla(topic, valor);
    } else {
      Serial.println("Error en publicar a MQTT.");
      actualitzarPantalla("MQTT ERROR", "No enviat");
    }
  }
}
