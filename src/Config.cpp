#include "Config.h"

void Config::SetHost(char* hostName){
    strcpy(host, hostName);
}
void Config::SetPort(int port){
    httpsport = port;
}
void Config::SetFingerprint(char* fingerprint){
    strcpy(this->fingerprint, fingerprint);
}
void Config::SetConnectionRetries(int retries){
    connectionRetries = retries;
}
void Config::SetReadTimeout(int timeout){
    readTimeout = timeout;
}

char* Config::GetHost(){
    return host;
}
int Config::GetPort(){
    return httpsport;
}
char* Config::GetFingerprint(){
    return fingerprint;
}
int Config::GetConnectionRetries(){
    return connectionRetries;
}
int Config::GetReadTimeout(){
    return readTimeout;
}