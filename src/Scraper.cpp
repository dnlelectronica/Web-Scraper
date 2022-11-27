#include "Scraper.h"

//Busca un string dentro de otro, 'n' veces.
//Devuelve el puntero con la posición de la cadena objetivo, si fue encontrada. Caso contrario, devuelve NULL.
//Ejemplo: source = 'Hola, esta función busca una cadena dentro de otra cadena.'
//         target = 'cadena'
//Si 'ocurrence' es igual a 1, devuelve el puntero en la posición de la primera ocurrencia (primer palabra 'cadena').
//Si 'ocurrence' es igual a 2, devuelve el puntero en la posición de la segunda ocurrencia (segunda palabra 'cadena').
 char* Scraper::SearchnString(char* source, const char* target, uint16_t ocurrence){
    resultPtr = source;
    
    for (uint16_t i=1; i <= ocurrence; i++){
        resultPtr = strstr(resultPtr, target);

        if ( (resultPtr == NULL) && (i == 1) ) //No hay ninguna ocurrencia.
            return NULL;
        if ( (resultPtr != NULL) && (i == ocurrence) ) //Encontro la cadena en el nro de ocurrencia solicitado
            return resultPtr;
        resultPtr++; //Continua buscando
        yield();
    }
    return NULL;
}

//Devuelve la subcadena presente entre dos delimitadores.
//Ejemplo: source = 'Hola, esta <funcion> busca una <cadena> entre dos delimitadores.'
//         start = '<' ; end = '>'
//Si 'ocurrence' es igual a 1, devuelve 'funcion'.
//Si 'ocurrence' es igual a 2, devuelve 'cadena'.
char* Scraper::Substring(char* source, const char* start, const char* end, uint16_t ocurrence){

    char* startPtr = SearchnString(source, start, ocurrence);//Solo busca 'n' ocurrencias de 'start'
    if (startPtr == NULL)
        return NULL;

    char* endPtr = SearchnString(startPtr, end, 1); //Busca siempre la primer ocurrencia después de 'start'.
    if (endPtr == NULL)
        return NULL;

    if (endPtr == startPtr) //Si los resultados de las búsquedas apuntan a la misma dirección, entonces 'end' y 'start' son iguales.
        return NULL;
    else{
        strncpy (substring, startPtr+strlen(start), endPtr-startPtr-strlen(start));
        return substring;
    }

    return NULL;
}

