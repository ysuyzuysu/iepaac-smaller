#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>              // Per a la comunicació I2C de la pantalla
#include <Adafruit_GFX.h>      // Llibreria de gràfics
#include <Adafruit_SSD1306.h>  // Llibreria de la pantalla SSD1306

// Configuració Pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins LoRa per a la TTGO T-Beam
#define SCK     5
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
const char* mqtt_topic = "ado/pot";

WiFiClient espClient;
PubSubClient client(espClient);

// Funció per mostrar missatges a la pantalla ràpidament
void actualitzarPantalla(String linia1, String linia2) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println(linia1);
  display.setCursor(0, 30);
  display.setTextSize(1);
  display.println(linia2);
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

  // 0. Inicialitzar Pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { 
    Serial.println(F("SSD1306 fallback"));
   // for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
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
  actualitzarPantalla("LORA: OK", "Esperant dades...");
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

    // Publicar al subtopic 'ado/pot'
    if (client.publish(mqtt_topic, message.c_str())) {
      Serial.println("Dades enviades al servidor.");
      
      // MOSTRAR EL MISSATGE QUE VOLIES A LA PANTALLA
      actualitzarPantalla("Enviant dades al", "servidor...");
      
      delay(1500); // Temps per llegir el missatge
      actualitzarPantalla("Darrera dada:", message);
    } else {
      Serial.println("Error MQTT.");
      actualitzarPantalla("MQTT ERROR", "No publicat");
    }
  }
}
