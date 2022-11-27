#ifndef SCRAPER_H
#include <string.h>
#include <Arduino.h>

#ifndef SUBSTRING_MAX_LENGTH
    #define SUBSTRING_MAX_LENGTH    512
#endif

class Scraper{
    private:
        char* resultPtr = NULL;
        char substring[SUBSTRING_MAX_LENGTH] = {0};
    public:
        char* SearchnString(char*, const char*, uint16_t);
        char* Substring(char*, const char*, const char*, uint16_t);
};

#endif