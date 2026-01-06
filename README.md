<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 80 80'%3E%3Ccircle cx='40' cy='40' r='38' fill='%233498db'/%3E%3Cellipse cx='40' cy='35' rx='18' ry='15' fill='%23ecf0f1'/%3E%3Cellipse cx='40' cy='60' rx='22' ry='10' fill='%23ecf0f1'/%3E%3Ccircle cx='32' cy='35' r='3' fill='%232c3e50'/%3E%3Ccircle cx='48' cy='35' r='3' fill='%232c3e50'/%3E%3C/svg%3E" alt="Project logo"></a>
</p>


<h1>Oil-Bot</h1>

# Sistema Inteligente de Monitoreo Acuático 🌊🤖

##  Descripción General

**Oil-Bot** es un proyecto de robótica avanzada desarrollado para competir en la categoría **"Futuros Innovadores"** de las **Olimpiadas Mundiales de Robótica (WRO)**. Este sistema autónomo representa una solución integral para la preservación de ecosistemas acuáticos, combinando ingeniería mecánica, electrónica de precisión y desarrollo de software en la nube.

El objetivo principal de Oil-Bot es realizar un monitoreo *in situ* de la calidad del agua, detectando anomalías químicas y físicas que podrían indicar contaminación, permitiendo una respuesta rápida ante desastres ambientales.

## 🚀 Características Destacadas

La complejidad técnica de Oil-Bot reside en su capacidad para integrar múltiples sistemas sensoriales y de comunicación en tiempo real:

*   **🔬 Análisis Multiparamétrico**: Equipado con sensores industriales para medir:
    *   **pH**: Nivel de acidez o alcalinidad del agua.
    *   **TDS (Sólidos Disueltos Totales)**: Indicador clave de la pureza del agua.
    *   **Temperatura**: Medición precisa mediante termopar Tipo K (MAX6675) para compensación de datos.
*   **🛰️ Navegación y Geolocalización**: Utiliza un módulo GPS dedicado para geoetiquetar cada muestra tomada, permitiendo la creación de mapas de calor de contaminación.
*   **☁️ Conectividad IoT Segura**: Transmisión de datos encriptada (HTTPS) hacia **Supabase**, permitiendo el almacenamiento histórico y el análisis remoto.
*   **🎮 Control Dual**: Sistema capaz de operar de forma autónoma o recibir comandos de dirección remotos desde la nube, adaptándose a entornos dinámicos.

## 🛠️ Arquitectura Técnica

El cerebro del sistema es un **ESP32**, elegido por su potencia de procesamiento dual-core y capacidades de conectividad Wi-Fi/Bluetooth.

### Stack de Tecnologías
*   **Firmware**: C++ (Arduino Framework).
*   **Backend**: Supabase (PostgreSQL + REST API).
*   **Protocolos**: HTTP/HTTPS, UART (GPS), SPI (Termopar), ADC (Sensores analógicos).
*   **Librerías Clave**: `ArduinoJson`, `TinyGPSPlus`, `WiFiClientSecure`.

### Estructura de Datos
El sistema gestiona dos flujos de información críticos:
1.  **Telemetría GPS**: Latitud, Longitud y Altitud.
2.  **Datos Ambientales**: Valores de pH, TDS y Temperatura compensada.

##  Importancia e Innovación

Oil-Bot no es solo un robot; es una propuesta tecnológica para enfrentar el cambio climático y la contaminación hídrica. Su desarrollo implicó resolver desafíos complejos como:
*   La gestión asíncrona de peticiones HTTP sin bloquear el control de motores.
*   La calibración y compensación térmica de sensores en tiempo real.
*   La integración de bases de datos relacionales en sistemas embebidos.

Este proyecto demuestra cómo la robótica educativa puede trascender el aula y ofrecer soluciones tangibles a problemas globales.

---
## 🏆 Sobre la Competencia

La **World Robot Olympiad (WRO)** es una competencia global que inspira a los jóvenes a interesarse por la ciencia y la tecnología. La categoría **Future Innovators** desafía a los equipos a desarrollar proyectos robóticos innovadores que resuelvan problemas del mundo real.

## 👥 Equipo

* **Alberto Medina** - Desarrollador Principal
*   **Ing. Daniel Cazorla** - Colaborador

---

## 📜 Licencia

Este proyecto está bajo la Licencia MIT.

**Contacto:** `Dcazorla.0190@gmail.com`