#include <WiFi.h> // Librería para conectividad Wi-Fi
#include <HTTPClient.h> // Librería para realizar solicitudes HTTP
#include <ArduinoJson.h> // Librería para manejar JSON
#include <WiFiClientSecure.h> // Para conexiones HTTPS seguras
#include <TinyGPSPlus.h> // Librería para parsear los datos NMEA del GPS
#include <HardwareSerial.h> // Para usar UART2 del ESP32
#include <SPI.h> // Librería para comunicación SPI
#include <max6675.h> // Librería para el sensor de temperatura MAX6675


// Pines del motor

#define motorDerecha_1 25
#define motorDerecha_2 26
#define motorIzquierda_1 27
#define motorIzquierda_2 14

// Credenciales Wi-Fi
#define MY_SSID "PROFESORES" // Mi casa
#define PASSWORD "i1Xzv8TZ8W06" // Mi casa

// #define MY_SSID "TP-Link_FD08" // Mi casa
// #define PASSWORD "C@s@_Bl@nc@" // Mi casa

// Definición de pines para el MAX6675 (Termopar Tipo K)
#define MAX6675_SCK_PIN 18
#define MAX6675_CS_PIN 19
#define MAX6675_SO_PIN 23
MAX6675 thermocouple(MAX6675_SCK_PIN, MAX6675_CS_PIN, MAX6675_SO_PIN);

// Definición de pines para el sensor TDS
#define TDS_SENSOR_PIN 34
#define VREF 3.3      // Voltaje de referencia del ADC
#define SCOUNT 30     // Número de muestras para promediar

// Variables para TDS
int analogBuffer[SCOUNT];    // Almacena los valores analógicos
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
float averageVoltage = 0;
float tdsValue = 0;

// Definición de pines para el sensor pH
#define PH_SENSOR_PIN 35
#define PH_OFFSET 0.0 // Ajuste de calibración para el pH

// Configuración Supabase
#define supabaseUrl "https://obdbtsmggdoedscydrob.supabase.co"
#define supabaseKey "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im9iZGJ0c21nZ2RvZWRzY3lkcm9iIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDg5OTE5NTMsImV4cCI6MjA2NDU2Nzk1M30.fUp5k5ECXePpMG1l8e_GZFOQKE_IArLvxg9gzfPm7hQ"
#define tablaDatos "datos"
#define tablaGPS "gps"

// Variables para sensores
float waterTemperature = 25; // Temperatura inicial para compensación TDS
float pHValue, pHVoltage;

TinyGPSPlus gps;
HardwareSerial SerialGPS(2);

void setup() {
  Serial.begin(115200); 
  SerialGPS.begin(115200, SERIAL_8N1, 16, 17);
  
  // Configuración de pines del motor
  pinMode(motorDerecha_1, OUTPUT);  
  pinMode(motorDerecha_2, OUTPUT);
  pinMode(motorIzquierda_1, OUTPUT);
  pinMode(motorIzquierda_2, OUTPUT);

  // --- Escaneo de Redes ---
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect();
  delay(100);
  
  // --- Intento de Conexión Wi-Fi ---
  WiFi.begin(MY_SSID, PASSWORD);
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - startTime < 30000)) {
    delay(1000);
  }

  // Inicialización del MAX6675
  pinMode(MAX6675_CS_PIN, OUTPUT);
  digitalWrite(MAX6675_CS_PIN, HIGH);
  SPI.begin();
  
  // Configuración de pines analógicos
  pinMode(TDS_SENSOR_PIN, INPUT);
  pinMode(PH_SENSOR_PIN, INPUT);
  delay(500); // Espera para estabilización
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    enviarDatosGPS();
    enviarDatos();
    obtenerDireccion();
  } else {
    WiFi.reconnect();
  }
  // Control del motor
  digitalWrite(motorDerecha_1, HIGH); // Motor derecho adelante
  digitalWrite(motorDerecha_2, LOW);
  digitalWrite(motorIzquierda_1, HIGH); // Motor izquierdo adelante
  digitalWrite(motorIzquierda_2, LOW);
  delay(500);
}

void enviarDatosGPS() { // Envia datos a Supabase
  float latitud = 0.0; // Inicializar variables
  float longitud = 0.0;
  float altitud = 0.0;
  // Leer datos del GPS
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }
  if (gps.location.isValid()) {
    latitud = gps.location.lat();
    longitud = gps.location.lng();
    altitud = gps.altitude.meters();
  }
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["latitud"] = latitud;
  jsonDoc["longitud"] = -63.843452; //longitud;
  jsonDoc["altitud"] = altitud;

  String jsonString; // Serializar el JSON
  serializeJson(jsonDoc, jsonString); // Convertir el documento JSON a una cadena
  Serial.print("Data GPS enviados: "); 
  Serial.println(jsonString);

  WiFiClientSecure client; // Cliente seguro para HTTPS
  // Desactivar la verificación del certificado SSL
  client.setInsecure(); 

  HTTPClient http; // Cliente HTTP para realizar solicitudes
  String endpoint = String(supabaseUrl) + "/rest/v1/" + tablaGPS; // Construir la URL del endpoint de Supabase
  http.begin(client, endpoint);

  http.addHeader("Content-Type", "application/json"); // Establecer contenido como JSON
  http.addHeader("apikey", supabaseKey); // Clave de API de Supabase
  http.addHeader("Authorization", "Bearer " + String(supabaseKey)); // Token de autorización
  http.addHeader("Prefer", "return=representation"); // Preferencia para que la respuesta incluya la representación del recurso creado

  http.POST(jsonString); // Enviar la solicitud POST con los datos JSON

  Serial.println("-------------------------------------------");
  Serial.println(String(http.connected()));
  Serial.println("-------------------------------------------"); 

  if (http.connected()){
    Serial.println("///////////////// CONECTO/////////////////////");
  }
  http.end(); // Finalizar la solicitud HTTP
}

void enviarDatos() { // Envia datos a Supabase
  // Leer sensores
  // TDS, pH y temperatura
  float tds = (leerTDS()); // TDS
  float ph = (leerPH()); // PH
  float temperatura = (leerTemperatura()); // temperatura

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["v1"] = tds;
  jsonDoc["v2"] = 7.5; //ph
  jsonDoc["v3"] = temperatura;

  String jsonString; // Serializar el JSON
  serializeJson(jsonDoc, jsonString); // Convertir el documento JSON a una cadena
  Serial.print("Data GPS enviados: "); 
  Serial.println(jsonString);

  WiFiClientSecure client; // Cliente seguro para HTTPS
  // Desactivar la verificación del certificado SSL
  client.setInsecure(); 

  HTTPClient http; // Cliente HTTP para realizar solicitudes
  String endpoint = String(supabaseUrl) + "/rest/v1/" + tablaDatos; // Construir la URL del endpoint de Supabase
  http.begin(client, endpoint);

  http.addHeader("Content-Type", "application/json"); // Establecer contenido como JSON
  http.addHeader("apikey", supabaseKey); // Clave de API de Supabase
  http.addHeader("Authorization", "Bearer " + String(supabaseKey)); // Token de autorización
  http.addHeader("Prefer", "return=representation"); // Preferencia para que la respuesta incluya la representación del recurso creado

  http.POST(jsonString); // Enviar la solicitud POST con los datos JSON
  http.end(); // Finalizar la solicitud HTTP
}

float leerTDS() {
  static unsigned long analogSampleTimepoint = millis();
  
  if (millis() - analogSampleTimepoint > 40U) { // Muestra cada 40ms
    analogSampleTimepoint = millis(); 
    analogBuffer[analogBufferIndex] = analogRead(TDS_SENSOR_PIN);
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT) {
      analogBufferIndex = 0;
    }
  }
  
  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U) {
    printTimepoint = millis();
    for (int copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }
    
    // Calcular el valor mediano
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4095.0;
    
    // Compensación por temperatura (usando la lectura actual del termopar)
    float compensationCoefficient = 1.0 + 0.02 * (waterTemperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;
    
    // Convertir voltaje a valor TDS
    return tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage 
              - 255.86 * compensationVoltage * compensationVoltage 
              + 857.39 * compensationVoltage) * 0.5;
  }else{
    if (tdsValue && tdsValue > 0.0) {
      return tdsValue;
    }else {
      return 0.0; // Retorna 0 si no hay datos válidos
    }
  }
}

int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

float leerPH() {
  // Leer 10 muestras y promediar para mayor estabilidad
  float pHReadings = 0;
  for (int i = 0; i < 10; i++) {
    pHReadings += analogRead(PH_SENSOR_PIN);
    delay(10);
  }
  pHVoltage = (pHReadings / 10) * VREF / 4095.0;
  pHValue = 3.5 * pHVoltage + PH_OFFSET; // Fórmula básica - calibrar según necesario
  if (pHValue && pHValue > 0.0) {
    return pHValue; // Asegurar que el pH no sea negativo
  }else {
    return 0.0; // Retornar 0 si no hay datos válidos
  }
}

float leerTemperatura() {
  digitalWrite(MAX6675_CS_PIN, LOW);
  delayMicroseconds(10); // Retardo crítico para comunicación estable
  
  float temp = thermocouple.readCelsius();
  
  digitalWrite(MAX6675_CS_PIN, HIGH);
  
  // Verificar si la lectura es válida
  if (isnan(temp) || temp == NAN) {
    Serial.println("Error en lectura de temperatura!");
    return -999.9; // Valor de error
  }
  if (temp && temp > 0.0) {
    return temp; // Asegurar que la temperatura no sea negativa
  }else {
    return 0.0; // Retornar 0 si no hay datos válidos
  }
}

void obtenerDireccion() { // control del bote
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  // Consulta el último registro de la tabla nuevo_gps
  String endpoint = String(supabaseUrl) + "/rest/v1/nuevo_gps?select=direccion&order=updated_at.desc&limit=1";
  http.begin(client, endpoint);

  http.addHeader("apikey", supabaseKey);
  http.addHeader("Authorization", "Bearer " + String(supabaseKey));

  int httpCode = http.GET();
  if (httpCode == 200) {
    String payload = http.getString();
    Serial.print("JSON recibido: ");
    Serial.println(payload);

    // Parsear el JSON para extraer el valor de direccion
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error && doc.size() > 0) {
      int direccion = doc[0]["direccion"];
      if (direccion == 1){
        digitalWrite(motorDerecha_1, HIGH); // Motor derecho adelante
        digitalWrite(motorDerecha_2, LOW);
        digitalWrite(motorIzquierda_1, LOW); // Motor izquierdo apagado
        digitalWrite(motorIzquierda_2, LOW);
        delay(2000);
      } else if (direccion == 0){
        digitalWrite(motorDerecha_1, LOW); // Motor derecho apagado
        digitalWrite(motorDerecha_2, LOW);
        digitalWrite(motorIzquierda_1, HIGH); // Motor izquierdo adelante
        digitalWrite(motorIzquierda_2, LOW);
        delay(2000);
      }
    } else {
      Serial.println("No se pudo extraer el campo 'direccion' del JSON.");
    }
  } else {
    Serial.print("Error HTTP: ");
    Serial.println(httpCode);
  }
  http.end();
  Serial.println("=================================================================================================");
}
