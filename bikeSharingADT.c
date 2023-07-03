#include "bikeSharingADT.h"
#include <stdlib.h>

// Sharing tipo "New York"
typedef struct rent1 {
    struct rent* a;
    char rideable_type;
    struct rent1* next;
} tRent1;

// Sharing tipo "Montreal"
// idem a struct rent

struct rent {
    char* start; // date or place
    char* end; // same
    size_t startId;
    size_t endId;
    char isMember;
};

struct station {
    char* station_name;
    double latitude;
    double longitude;
    unsigned int id;
};

// Station tipo "New York" (lista)
typedef struct {
    struct station stationInfo;
    tRent1 * list;
} tStationList;

// Station tipo "Montreal" (vector)
typedef struct {
    struct station stationInfo;
    struct rent* rentInfo;
} tStationArray;


// Guardar de forma ordenada (alfab) o despues sortear?
typedef struct bikeSharingCDT {
     tStationList* station1;
     tStationArray* station2;
    int (*compare)(char* source, char* target);
} bikeSharingCDT;

