#ifndef CONFIG_h
#define CONFIG_H

#include <Arduino.h>

#ifndef HOST_MAX_LENGTH
    #define HOST_MAX_LENGTH     256
#endif
#ifndef READ_TIMEOUT
    #define READ_TIMEOUT        10000
#endif
#ifndef CONNECTION_RETRIES
    #define CONNECTION_RETRIES  5
#endif

class Config{
    private:
        char host[HOST_MAX_LENGTH];
        int httpsport;
        char fingerprint[60];
        int connectionRetries;
        int readTimeout;

    public:
        Config(){ httpsport = 443; connectionRetries = CONNECTION_RETRIES; readTimeout = READ_TIMEOUT; }
        Config(char* host, char* fingerprint){ 
            strcpy(this->host, host);
            strcpy(this->fingerprint, fingerprint);
            httpsport = 443;
            connectionRetries = CONNECTION_RETRIES;
            readTimeout = READ_TIMEOUT;
        }

        void SetHost(char*);
        void SetPort(int);
        void SetFingerprint(char*);
        void SetConnectionRetries(int);
        void SetReadTimeout(int);

        char* GetHost();
        int GetPort();
        char* GetFingerprint();
        int GetConnectionRetries();
        int GetReadTimeout();
};

#endif