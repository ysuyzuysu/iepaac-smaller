# 📡 Monitorització LoRa T-Beam: Receptor

Aquest repositori conté el codi del receptor per a una placa **TTGO T-Beam** que llegeix dades analògiques, les mostra en una pantalla OLED integrada i les transmet via LoRa.

## 🛠️ Requisits de Hardware

* **Placa:** TTGO T-Beam (ESP32 + LoRa + Pantalla OLED SSD1306).
* **Antena:** 868 MHz connectada obligatòriament abans d'encendre.

## 💻 Configuració de VS Code + PlatformIO

1. Instal·leu l'extensió **PlatformIO IDE** a VS Code.
2. Substituïu el contingut del vostre fitxer `platformio.ini` per aquest bloc:

```ini
[env:ttgo-t-beam]
platform = espressif32
board = ttgo-t-beam
framework = arduino
lib_deps = 
	sandeepmistry/LoRa @ ^0.8.0
	knolleary/PubSubClient @ ^2.8
	thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.4.1
monitor_speed = 115200


```

## 🔌 Esquema de Connexions i Pantalla

| Component | Pin Origen | Pin T-Beam |
| --- | --- | --- |
| **Pantalla OLED** | SDA | **GPIO 21** |
| **Pantalla OLED** | SCL | **GPIO 22** |
| **Pantalla OLED** | VCC | **GPIO 3.3V** |
| **Pantalla OLED** | GND | **GPIO GND** |

## 🚀 Instruccions de Flashing

1. Connecteu la T-Beam al port USB.
2. Copieu el codi al fitxer `src/main.cpp`.
3. Premeu la icona **Build** (✓) i després **Upload** (→).
4. Obriu el **Serial Monitor** (🔌) per verificar el sistema.

## 🖥️ Solució de problemes: Pantalla en negre

Si la pantalla no mostra text un cop flashejat el codi, seguiu aquests passos:

1. **Adreça I2C:** El codi prova automàticament `0x3C` i `0x3D`. Si no funciona, comproveu el monitor sèrie per veure si es detecta el dispositiu.
2. **Reset Físic:** Moltes T-Beam necessiten que el pin **16** es posi en `LOW` i després en `HIGH` per despertar la pantalla. El codi inclòs ja realitza aquesta seqüència.
3. **Alimentació:** Assegureu-vos que la placa rep prou corrent via USB, ja que la pantalla i el mòdul LoRa consumeixen pics d'energia significatius.


---


