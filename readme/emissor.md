# 📡 Monitorització LoRa T-Beam: pH & Potenciòmetre

Aquest repositori conté el codi de l'emissor per a una placa **TTGO T-Beam** que llegeix dades analògiques, les mostra en una pantalla OLED integrada i les transmet via LoRa.

## 🛠️ Requisits de Hardware

* **Placa:** TTGO T-Beam (ESP32 + LoRa + Pantalla OLED SSD1306).
* **Sensor de pH:** Mòdul PH-4502C connectat al **GPIO 32**.
* **Potenciòmetre:** Connectat al **GPIO 35**.
* **Antena:** 868 MHz connectada obligatòriament abans d'encendre.
* **Sensor de Temperatura/Humitat, DHT11:** Sensor (opcional) per a medir la temperatura i humitat. 
## 💻 Configuració de VS Code + PlatformIO

1. Instal·leu l'extensió **PlatformIO IDE** a VS Code.
2. Substituïu el contingut del vostre fitxer `platformio.ini` per aquest bloc:

```ini
[env:ttgo-t-beam]
platform = espressif32
board = ttgo-t-beam
framework = arduino
monitor_speed = 115200
lib_deps =
    sandeepmistry/LoRa @ ^0.8.0
    adafruit/Adafruit SSD1306 @ ^2.5.7
    adafruit/Adafruit GFX Library @ ^1.11.7
    adafruit/Adafruit BusIO @ ^1.14.1

```

## 🔌 Esquema de Connexions i Pantalla

| Component | Pin Origen | Pin T-Beam |
| --- | --- | --- |
| **Pantalla OLED** | VCC | **3,3V** |
| **Pantalla OLED** | SDA | **GPIO 21** |
| **Pantalla OLED** | SCL | **GPIO 22** |
| **Pantalla OLED** | Reset | **GPIO 16** (o automàtic) |
| **Sensor pH** | Senyal (Po) | **GPIO 32** |
| **Potenciòmetre** | Senyal | **GPIO 35** |
| **Sensor de Humitat** | Senyal | **GPIO 14** |
| **Sensor de Humitat** | VCC | **5V** |

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

## ⚙️ Calibratge del pH

El sistema calcula el pH basant-se en una referència de voltatge. Si el valor és incorrecte:

* Introduïu la sonda en una solució neutra (pH 7).
* Ajusteu el cargol del potenciòmetre blau de la placa del sensor fins que la pantalla mostri **pH: 7.00**.

---

Vols que t'adjunti també el bloc de codi `main.cpp` final sense comentaris per completar el teu repositori?
