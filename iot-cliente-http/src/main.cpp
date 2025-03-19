#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>
#include <HTTPClient.h>
#define LED 2

const char *ssid = "Familia_Ricardo";
const char *passsword = "Juank172";
const char *thingAPI = "http://codelab.denkitronik.com:8080/thingname/230212001?estado";

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando cliente http");
  conectarWifi(ssid, passsword);
}

void loop(){
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    // Generar valores aleatorios dentro de un rango
    float temperatura = random(200, 350) / 10.0;
    float humedad = random(400, 800) / 10.0;

    // String url = "/update?api_key=" + apiKey + "&field1=" + String(temperatura) + "&field2=" + String(humedad);
    String url = "http://codelab.denkitronik.com:8080/thingname/230212001?humedad=" + String(humedad) + "&temperatura=" + String(temperatura);

    // Enviar la solicitud HTTP GET
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      String payload = http.getString();
      Serial.println("Respuesta del servidor: " + payload);
    }
    else
    {
      Serial.println("Error en la solicitud" + String(httpCode));
    }
    http.end();
  }
  else
  {
    Serial.println("Error en la conexion wifi");
  }
  delay(10000);
}