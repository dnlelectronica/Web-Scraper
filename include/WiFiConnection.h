#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H
#include <ESP8266WiFi.h>

class WiFiConnection
{
    private:

        const char *SSID = ""; //WIFI SSID
        const char *PASS = ""; //WIFI PASSWORD
        const int WIFI_RETRIES = 5;

    public:
        bool Init();
        wl_status_t GetCurrentStatus();
        IPAddress GetLocalIP();
        const char* GetCurrentSSID();
};
#endif
