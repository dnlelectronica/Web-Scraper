#include "WiFiConnection.h"


//Inicializa el módulo WiFi y conecta con la red especificada. 
//Devuelve true si la conexión fue satisfactoria.
bool WiFiConnection::Init(){
    int retriesCounter = 0;

    WiFi.mode(WIFI_OFF); //Si el módulo estaba previamente conectado, lo desconecta.
    delay(1000);
    WiFi.mode(WIFI_STA); //Modo estación.
    WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED) {
        if (retriesCounter++ >= WIFI_RETRIES)
            return false;
        delay(1000);
    }
    
    return true;
}

const char* WiFiConnection::GetCurrentSSID(){
    return SSID;
}
wl_status_t WiFiConnection::GetCurrentStatus(){
    return WiFi.status();
}
IPAddress WiFiConnection::GetLocalIP(){
    return WiFi.localIP();
}