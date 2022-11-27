#ifndef HTTPSECCLIENT_H
#define HTTPSECCLIENT_H
#include <WiFiClientSecure.h>
#include "Config.h"

#ifndef REQUEST_MAX_LENGTH
    #define REQUEST_MAX_LENGTH  1024
#endif
#ifndef BODY_MAX_LENGTH
    #define BODY_MAX_LENGTH     8192
#endif

class HTTPSecClient
{
    private:

        WiFiClientSecure httpsClient;
        Config localConfig;      
        
        char request[REQUEST_MAX_LENGTH] = {0};
        char body[BODY_MAX_LENGTH] = {0};

        char* FormatGETRequest(const char*);
        bool CheckResponse(char*);

    public:
        void Init(Config);
        bool Connect();
        bool SendRequest(const char*);
        char* GetResponseBody();
        int DiscardBytesBefore(const char*);
};


#endif