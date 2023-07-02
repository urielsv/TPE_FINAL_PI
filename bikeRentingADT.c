#include "bikeRentingADT.h"
#include <stdlib.h>


// Renting tipo "New York"
typedef struct {
    // Todos los atributos (hay inecesarios)
    size_t started_at;
    size_t start_station_id;
    size_t ended_at;
} tRentType1;

// Renting tipo "Montreal"
typedef struct {
//a
} tRentType2;

struct station {
    char* station_name;
    double latitude;
    double longitude;
    unsigned int id;
};

// Station tipo "New York" (lista)
typedef struct {
    struct station stationInfo;
    //lista
} tStationType1;

// Station tipo "Montreal" (vector)
typedef struct {
    struct station stationInfo;
    tRentType2 * rentInfo;
} tStationTypeArray;

typedef struct bikeRentingCDT {
     tStationTypeList * station1;
     tStationTypeArray * station2;
    int (*compare)(char* source, char* target);
} bikeRentingCDT;