# IEPAAC-Smaller: Sistema de Monitorització de pH Marí 🌊

Un projecte IoT basat en tecnologia LoRa, dissenyat per a la monitorització de la vida marina en un entorn educatiu. Aquest projecte ha estat desenvolupat pel grup **Hydrahub**. 

Com que no teníem coneixements previs de programació en C++, hem utilitzat la Intel·ligència Artificial (**Google Gemini**) per a crear tota la lògica del programari.

---

## 🚀 Característiques Principals

* **Transmissió sense fils:** Utilitza tecnologia LoRa per enviar dades a llargues distàncies sense necessitat de Wi-Fi ni Bluetooth.
* **Monitorització de pH en temps real:** Sensor integrat per mesurar l'acidesa de l'aigua en entorns marins.
* **Integració MQTT:** Gestió de dades centralitzada mitjançant una Raspberry Pi que actua com a servidor (broker).
* **Desenvolupament assistit per IA:** Programat íntegrament amb l'ajuda de Gemini, optimitzant tasques que requeririen coneixements avançats de C++.
* **Disseny de baix consum:** Optimitzat per a plaques LILYGO T-BEAM (AXP2101).

---

## 🛠️ Materials Necessaris

Per replicar aquest projecte, necessitareu els següents components:

| Component | Descripció |
| :--- | :--- |
| **Microcontroladors** | 2x LILYGO T-BEAM AXP2101-V1.2 (LoRa32) |
| **Antenes** | 2x Antenes LoRa (Molt important: no encendre les plaques sense l'antena!) |
| **Sensor de pH** | 1x Kit PH meter (Sonda + placa de calibratge) |
| **Servidor** | 1x Raspberry Pi (amb servidor MQTT configurat) |
| **Control** | 1x Potenciòmetre (per a calibratge/ajustos) |
| **Cables** | Pack de cables Dupont (M-F, F-F) i 2x cables Micro-USB |
| **PC** | Ordinador Windows o Linux per compilar el codi |

---

## 💻 Programari i Eines

* **Llenguatge:** C++ (Arduino Framework).
* **IDE:** [VS Code](https://code.visualstudio.com/) o [CodeOSS](https://vscodium.com/).
* **Extensió:** [PlatformIO IDE](https://platformio.org/).

---

## 📂 Estructura del Projecte

El projecte es divideix en 4 parts principals. Consulteu els seus README específics per a més detalls:

1.  **[Emissor](https://github.com/ysuyzuysu/iepaac-smaller/blob/main/readme/emissor.md):** Recull les dades del sensor de pH i les envia per LoRa.
2.  **[Receptor](https://github.com/ysuyzuysu/iepaac-smaller/blob/main/readme/receptor.md):** Rep els paquets LoRa i els reenvia al servidor MQTT.
3.  **[Servidor MQTT](https://github.com/ysuyzuysu/iepaac-smaller/blob/main/readme/mqtt.md):** Instruccions per configurar la Raspberry Pi per guardar les dades.
4.  **[NodeRED](https://github.com/ysuyzuysu/iepaac-smaller/blob/main/readme/nodered.md):** Instruccions per configurar **EN** la Raspberry Pi les instruccions.

---

## 🔧 Configuració Inicial

1.  **Preparació de l'entorn:** Instal·la VS Code i l'extensió PlatformIO.
2.  **Preparació del Hardware:** Solda els pins a les plaques T-BEAM i **enrosca les antenes LoRa** abans de connectar-les al corrent.
3.  **Pujada del codi:** * Connecta l'Emissor per USB i puja el codi des de PlatformIO.
    * Repeteix el procés per al node Receptor.
4.  **Configuració MQTT:** Assegura't que la Raspberry Pi estigui a la mateixa xarxa i que la IP estigui correctament configurada al codi del Receptor.

---

## 📝 Crèdits i Reconeixements

Aquest projecte ha estat creat pel grup **Hydrahub**. Tot i que sabem que podríem haver utilitzat altres models com Claude (Anthropic), hem optat per Google Gemini per a tota la programació i estructura del projecte.

---
