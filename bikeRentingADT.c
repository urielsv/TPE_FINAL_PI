#include"bikeRentingADT.h"
#include <stdlib.h>

// Renting tipo "New York"
typedef struct rent1 {
    // Todos los atributos (hay innecesarios)
    size_t startedAt;
    size_t startStationId;
    size_t endedAt;
    struct rent1 * next;
} tRentType1;

// Renting tipo "Montreal"
typedef struct rent2 {
    //Todos los atributos (hay innecesarios)
    unsigned char startDate; // monthStart
    unsigned int emplacementPkStart;
    unsigned char endDate;
    unsigned int emplacementPkeEnd;
    char isMember;
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
    tRentType1 * list;
} tStationTypeList;

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

