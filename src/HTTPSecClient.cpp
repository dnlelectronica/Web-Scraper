#include "HTTPSecClient.h"
#include <string.h>


//Inicializa el cliente, utilizando los parámetros cargados en un objeto de la clase 'Config'.
void HTTPSecClient::Init(Config conf){
    localConfig = conf;

    httpsClient.setFingerprint(localConfig.GetFingerprint());
    httpsClient.setTimeout(localConfig.GetReadTimeout());
}

//Conecta con el servidor. Devuelve false si ningún intento de conexión fue satisfactorio.
bool HTTPSecClient::Connect(){
    int retriesCounter = 0;
    
    while (!httpsClient.connect(localConfig.GetHost(), localConfig.GetPort())){
        if (retriesCounter++ >= localConfig.GetConnectionRetries())
            return false;
        delay(500);
    }
    return true;
}
//Envía una petición GET al endPoint y espera respuesta. Retorna true si la respuesta del servidor fue "OK" (200)
bool HTTPSecClient::SendRequest(const char* endPoint){
    uint16_t bytesToRead = 0;
    char localHeaderBuffer[256] = {0};

    if (httpsClient.connected())
        httpsClient.print(FormatGETRequest(endPoint));
    
    //Lee los bytes enviados por el servidor hasta encontrar un fin de línea o hasta llenar el buffer.
    //En este caso, sólo se va a leer la primer línea del header, que es donde se encuentra el código de estado de la petición.
    bytesToRead = httpsClient.readBytesUntil('\n', localHeaderBuffer, sizeof(localHeaderBuffer));
    
    if (bytesToRead == 0)
        return false;
    
    if (CheckResponse(localHeaderBuffer))
        return true;
    else
        return false;
}

char* HTTPSecClient::GetResponseBody(){
    uint16_t bytesToRead = 0;

    bytesToRead = httpsClient.readBytes(body, sizeof(body));
    body[bytesToRead] = '\0';
    return body;
}

//Descarta los bytes recibidos hasta encontrar el parámetro (el mismo también se descarta).
//De esta manera, se evita el llenado del buffer del módulo ESP8266 con datos innecesarios.
//Ejemplo: 
//  Se recibe la siguiente cadena en el buffer -> <!doctype html><html lang="es-ar"><head>...</head><body>abc</body></html>
//  DiscardBytesBefore("<body>") -> Deja en el buffer lo siguiente: abc</body></html>

//Retorna -1 si hubo error de lectura; 0 si no hay datos; 1 si hay.
int HTTPSecClient::DiscardBytesBefore(const char* param){
    char character = 0;
    
    for (uint16_t i=0; i < strlen(param); ){
        character = httpsClient.read();
        if (character == -1)
            return -1;
        else if (character == 0)
            return 0;
        i = (character == param[i]) ? (i+1) : 0;
    }

    return 1;
}

//Arma el string de la petición según el parámetro dado.
char* HTTPSecClient::FormatGETRequest(const char* endPoint){
    memset (request, 0, sizeof(request));
    sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", endPoint, localConfig.GetHost());
    return request;        
}

//Comprueba si la respuesta del servidor fue "OK"(200).
bool HTTPSecClient::CheckResponse(char* responseString){
    if (strstr(responseString, "200") != NULL)    
        return true;
    return false;
}
