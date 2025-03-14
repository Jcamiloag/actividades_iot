#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>
#define LED 2

const char * ssid = "Familia_Ricardo";
const char * passsword = "Juank172";
const char * host = "api.thingspeak.com";
const int port = 80;
const String apiKey = "9XYOXKFXD9L2S8QE";

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando cliente http");
  conectarWifi(ssid,passsword);
}

void loop() {
  WiFiClient cliente;
  if(!cliente.connect(host, port)){
    delay(2000);
    return;
  }
  
  // Generar valores aleatorios dentro de un rango
  float temperatura = random(200, 350) / 10.0; 
  float humedad = random(400, 800) / 10.0; 

  String url = "/update?api_key=" + apiKey + "&field1=" + String(temperatura) + "&field2=" + String(humedad);

  // Enviar la solicitud HTTP GET
  cliente.print("GET " + url + " HTTP/1.1\r\n");
  cliente.print("Host: " + String(host) + "\r\n");
  cliente.print("Connection: close\r\n\r\n");

  // Agregamos un tiempo de espera para recibir los primeros caracteres del servidor 
  unsigned long tiempo = millis();
  while(cliente.available() == 0){
    if(millis() - tiempo > 5000){
      Serial.println("Se agota el tiempo de espera");
      cliente.stop();
      return;
    }
  }
  while (cliente.available()){
    String linea = cliente.readStringUntil('\r');
    Serial.println(linea);
  }
  Serial.println("Finalizando conexion");
  cliente.stop();
  delay(4000);
}




