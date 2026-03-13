/**
 * PROJECTE: Receptor LoRa amb T-Beam (ADO)
 * DESCRIPCIÓ: Rep dades de PH, Potenciòmetre, Temperatura i Humitat via LoRa,
 * les mostra per pantalla OLED i les envia a un servidor MQTT.
 */

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SSD1306Wire.h>

// ==========================================
// 1. CONFIGURACIÓ DE PINS I PANTALLA
// ==========================================

// Pins per a la pantalla OLED SSD1306 (I2C)
#define OLED_SDA 21
#define OLED_SCL 22
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

// Pin analògic per llegir el voltatge de la bateria (divisor de tensió intern)
#define BATT_PIN 35

// Pins per al mòdul LoRa (SPI i control)
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

// ==========================================
// 2. CONFIGURACIÓ WIFI I MQTT
// ==========================================

const char* ssid = "Aula 23";
const char* password = "223AuLa23";
const char* mqtt_server = "192.168.223.50";

WiFiClient espClient;
PubSubClient client(espClient);

// ==========================================
// 3. FUNCIONS DE GESTIÓ DE BATERIA
// ==========================================

/**
 * Calcula el percentatge aproximat de la bateria 18650.
 * Utilitza analogRead sobre el pin 35 i aplica la fórmula del divisor de tensió.
 */
String obtenirPercentatgeBateria() {
  int rawValue = analogRead(BATT_PIN);
  
  // Fórmula: (valor / resolució) * voltatge_referència * factor_divisor
  float voltage = (rawValue / 4095.0) * 3.3 * 2.0;
  
  // Mapatge: 3.2V = 0% | 4.2V = 100%
  int percent = map(voltage * 100, 320, 420, 0, 100);
  
  // Limitem els valors entre 0 i 100
  if (percent > 100) percent = 100;
  if (percent < 0) percent = 0;
  
  return String(percent) + "%";
}

// ==========================================
// 4. FUNCIONS D'INTERFÍCIE (PANTALLA)
// ==========================================

/**
 * Neteja la pantalla i escriu les dades actuals i l'estat de la bateria.
 */
void actualitzarPantalla(String linia1, String linia2) {
  display.clear();
  display.setFont(ArialMT_Plain_10);
  
  // Part superior: Percentatge de bateria
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 0, obtenirPercentatgeBateria());
  
  // Part central i inferior: Tòpic i Valor rebut
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 15, linia1); // Tòpic (ex: ado/TEMP)
  display.drawString(0, 35, linia2); // Valor (ex: 24.5)
  
  display.display();
}

// ==========================================
// 5. FUNCIONS DE XARXA (MQTT)
// ==========================================

/**
 * Gestiona la reconnexió automàtica al servidor MQTT en cas de pèrdua.
 */
void reconnect() {
  while (!client.connected()) {
    // Intentem connectar amb un ID de client únic
    if (client.connect("TBeam_Receptor_ADO")) {
      break; 
    } else {
      // Si falla, esperem 5 segons abans de tornar-ho a provar
      delay(5000);
    }
  }
}

// ==========================================
// 6. CONFIGURACIÓ INICIAL (SETUP)
// ==========================================

void setup() {
  Serial.begin(115200);
  
  // Configura el pin de la bateria
  pinMode(BATT_PIN, INPUT);

  // Inicialitza la pantalla OLED
  display.init();
  display.flipScreenVertically();
  actualitzarPantalla("Iniciant...", "Espereu...");

  // Connexió a la xarxa WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
  }
  
  // Configura el servidor MQTT
  client.setServer(mqtt_server, 1883);

  // Inicialitza el bus SPI i el mòdul LoRa (868 MHz)
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(868E6)) {
    actualitzarPantalla("ERROR LORA", "Revisa pins");
    while (1); // Atura el programa si LoRa falla
  }
  
  actualitzarPantalla("LORA: OK", "Escoltant...");
}

// ==========================================
// 7. BUCLE PRINCIPAL (LOOP)
// ==========================================

void loop() {
  // Manté la connexió MQTT activa
  if (!client.connected()) reconnect();
  client.loop();

  // Comprova si hi ha paquets LoRa nous
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    
    // Llegim el contingut del missatge LoRa
    while (LoRa.available()) { 
      message += (char)LoRa.read(); 
    }

    String topic = "";
    String valor = "";

    // LÒGICA DE SEPARACIÓ (Parsing)
    // Busquem l'etiqueta inicial per decidir a quin tòpic MQTT publicar
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

    // Publiquem la dada al broker MQTT i actualitzem la pantalla OLED
    if (client.publish(topic.c_str(), valor.c_str())) {
      actualitzarPantalla(topic, valor);
    }
  }
}
