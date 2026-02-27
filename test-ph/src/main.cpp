#include <Arduino.h>

// --- Configuración de Pines ---
#define PIN_PH 32 

void setup() {
  Serial.begin(115200);
  
  // Resolución de 12 bits para ESP32 (0 - 4095)
  analogReadResolution(12);
  
  Serial.println("===========================================");
  Serial.println("   DIAGNÓSTICO COMPLETO: VOLTAJE + PH    ");
  Serial.println("===========================================");
}

void loop() {
  // 1. Lectura bruta del ADC
  int adcRaw = analogRead(PIN_PH);
  
  // 2. Conversión a Voltaje (Referencia 3.3V)
  float voltatge = adcRaw * (3.3 / 4095.0);

  // 3. Cálculo de pH 
  // Usamos la fórmula estándar: pH 7 está en 1.65V (la mitad de 3.3V)
  // Cada unidad de pH equivale aproximadamente a 0.18V - 0.20V (3.5 de pendiente)
  float valorPH = 7.0 + ((1.65 - voltatge) * 3.5); 

  // --- IMPRESIÓN DE DATOS ---
  Serial.print("ADC: "); 
  Serial.print(adcRaw);
  
  Serial.print(" | VOLTAJE: "); 
  Serial.print(voltatge, 3); 
  Serial.print("V");

  Serial.print(" | PH ESTIMADO: "); 
  Serial.println(valorPH, 2);

  // --- AYUDA VISUAL ---
  if (voltatge < 0.60) {
    Serial.println("  --> [!] AVISO: Voltaje muy bajo. El pH sale alto (>10) porque el sensor no envía señal.");
  } else if (voltatge > 3.0) {
    Serial.println("  --> [!] AVISO: Voltaje muy alto. El pH sale bajo (<2). Revisa si hay un cortocircuito.");
  }

  delay(1000); 
}