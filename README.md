# 🌊 Sistema Inteligente de Monitoreo Acuático con ESP32

*Monitoreo en tiempo real de calidad de agua con toma de decisiones asistida por IA*

## 📌 Descripción
Sistema IoT para monitorear cuerpos de agua que:
1. **Mide parámetros** (pH, conductividad, temperatura)  
2. **Geolocaliza** muestras con GPS  
3. **Toma decisiones** con IA (Gemini) sobre dirección de botes  
4. **Visualiza datos** en dashboard web en tiempo real  

---

## ⚙️ Componentes Principales

### 🔌 Hardware (ESP32)
| Componente               | Función                                  |
|--------------------------|------------------------------------------|
| Sensores de calidad agua | pH, conductividad, temperatura           |
| 2 Motores sumergibles    | Movimiento del bote                      |
| Driver dual L298N        | Control de motores                       |
| Módulo GPS NEO-6M        | Geolocalización                          |

### 🌐 Software
| Componente          | Tecnología          | Función                                  |
|---------------------|---------------------|------------------------------------------|
| Backend            | Python              | Procesamiento de datos e integración con Gemini API |
| Frontend Web       | HTML/CSS/JS         | Dashboard y mapa en tiempo real          |
| Autenticación      | Firebase Auth       | Gestión de usuarios                     |
| Base de datos      | Supabase            | Almacenamiento histórico                |
| Hosting            | Firebase Hosting    | Despliegue de la web                    |

---

## 🔄 Flujo del Sistema
- Recolección: ESP32 mide parámetros y GPS

- Transmisión: Envía datos a Supabase via WiFi

- Procesamiento: Backend consulta a Gemini API con coordenadas

- Acción: ESP32 recibe decisión (1/0) y controla motores

- Visualización: Web muestra datos y ubicación en mapa en vivo

## 🖥️ Estructura de Archivos
```text
├── ESP32/
│   ├── main.ino            # Código principal
│   └── gps.txt            # Datos GPS de prueba
├── servidor/
│   ├── main.py            # Backend Flask
│   └── config.py         # Configuración API
├── public/                # Web App
│   ├── css/
│   ├── js/
│   ├── index.html        # Dashboard
│   └── monitoring.html  # Mapa en tiempo real
└── firebase-config/      # Auth y Hosting
```
## 🌟 Características Clave
- Toma de decisiones con IA: Gemini analiza coordenadas para dirección óptima

- Mapa interactivo: Visualización en tiempo real con Leaflet/Google Maps

- Control autónomo: Motores se ajustan según análisis de calidad de agua

- Autenticación segura: Firebase Auth para acceso al dashboard

📜 Licencia
MIT License - Ing. Daniel Cazorla / Dcazorla.0190@gmail.com
