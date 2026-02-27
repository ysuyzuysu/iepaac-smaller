# IEPAC-Smaller: Marine pH Monitoring System 🌊

A LoRa-based IoT project designed for marine life monitoring in an educational environment. Will be used on an Institute about Marine Life.

---

## 🚀 Key Features

* **Wireless Data Transmission:** Uses LoRa technology to send sensor data over long distances without needing Wi-Fi or Bluetooth.
* **Real-time pH Monitoring:** Integrated sensor logic to track water acidity levels in marine environments.
* **MQTT Integration:** Centralized data management using a Raspberry Pi as a broker.
* **AI-Powered Development:** Entirely programmed using **Google Gemini**, showcasing the potential of LLMs in STEM education.
* **Low Power Design:** Optimized for LILYGO T-BEAM boards (AXP2101) for field deployment.

---

## 🛠️ Hardware Requirements

To build this project, you will need the following components:

| Component | Description |
| :--- | :--- |
| **Microcontrollers** | 2x LILYGO T-BEAM AXP2101-V1.2 (LoRa32) |
| **Antennas** | 2x LoRa Antennas (Essential: do not power on without them!) |
| **pH Sensor** | 1x pH Meter Kit (Sensor probe + Calibration board) |
| **Server** | 1x Raspberry Pi (Running an MQTT Broker) |
| **Control** | 1x Potentiometer (For sensor calibration) |
| **Cables** | Dupont pack (M-F, F-F) & 2x Micro-USB cables |
| **OS** | Windows or Linux PC for compilation |

---

## 💻 Software & Tools

* **Language:** C++ (Arduino Framework).
* **IDE:** [VS Code](https://code.visualstudio.com/) or [CodeOSS](https://vscodium.com/).
* **Extension:** [PlatformIO IDE](https://platformio.org/).
* **AI Tools:** [Google Gemini](https://gemini.google.com/) (Mainly used for code generation).

---

## 📂 Project Structure & Documentation

The project is organized into three main modules. Please refer to their specific READMEs for detailed instructions:

1.  **[Emitter Node (Transmitter)](link_here):** Collects pH data and sends it via LoRa.
2.  **[Receiver Node](link_here):** Receives LoRa packets and forwards them to the MQTT server.
3.  **[MQTT Server Setup](link_here):** Instructions on how to configure the Raspberry Pi to store and display data.

---

## 🔧 Getting Started

1.  **Setup the Environment:** Install VS Code and the PlatformIO extension.
2.  **Hardware Prep:** Solder the pins to the T-BEAM boards and **screw on the LoRa antennas** before connecting them to power.
3.  **Flash the Boards:** * Connect the Emitter via USB and upload the code using PlatformIO.
    * Repeat the process for the Receiver node.
4.  **Configure MQTT:** Ensure your Raspberry Pi is on the same network and the IP address is correctly set in the Receiver's code.

---

## 📝 Credits & Acknowledgments

This project was created by students for a marine biology initiative. Since we lacked deep knowledge in C++, we leveraged **Google Gemini** to write the logic and structure the communication protocols. 

> **Note:** While we chose Gemini for this task, other models like Claude (Anthropic) are also great alternatives for C++ programming.

---
