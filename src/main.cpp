#include <Arduino.h>
#include "HTTPSecClient.h"
#include "WiFiConnection.h"
#include "Scraper.h"

#define UPDATE_PERIOD   10000 //Intervalo de petición de cotización, expresados en milisegundos.

WiFiConnection wifiConnection;
HTTPSecClient httpsClient;
Scraper scraper;

Config site1((char*)"dolarhoy.com", (char*)"AB E9 7D 4C A4 1F EE 25 72 3C D5 D2 73 D0 AD 89 D1 FF E0 BB");

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.print("Conectando a ");
  Serial.println(wifiConnection.GetCurrentSSID());

  if (wifiConnection.Init())
    Serial.println ("Conexion establecida.");
  else{
    Serial.println ("No se pudo conectar con la red.");
    Serial.println ("Reiniciando módulo...");
    ESP.restart();
  }

  Serial.print("IP Local: ");
  Serial.println(wifiConnection.GetLocalIP());  

  httpsClient.Init(site1);
}

void Run(){
  char* response = NULL;
  
  Serial.println("Conectando al sitio... ");

  if (httpsClient.Connect())
    Serial.println("Conectado al sitio.");
  else{
    Serial.println("No se pudo conectar al sitio.");
    return;
  }

  Serial.println("Enviando peticion...");
  
  if (!httpsClient.SendRequest("/i/cotizaciones/dolar-bancos-y-casas-de-cambio")){
    Serial.println("Error de comunicación con el sitio.");
    return;
  }
  
  Serial.println("Header OK");
    
  if (httpsClient.DiscardBytesBefore("<div class=\"data__valores\">")){
      response = httpsClient.GetResponseBody();
      Serial.println("RESPONSE: \r\n");
      
      Serial.print(scraper.Substring(response, "<span>", "</span>", 1));
      Serial.print(": ");
      Serial.println(scraper.Substring(response, "<p>", "<span>", 1));
      Serial.print(scraper.Substring(response, "<span>", "</span>", 2));
      Serial.print(": ");
      Serial.println(scraper.Substring(response, "<p>", "<span>", 2));
  }
}

void loop() {
  Run();
  delay(UPDATE_PERIOD);
}