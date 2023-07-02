#include "bikeRentingADT.h"
#include "stdlib.h"

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
    string station_name;
    latitude;
    longitude
    id;
};

// Station tipo "New York"
typedef struct {
    struct station stationInfo;
    //lista
} tStationType1;

// Station tipo "Montreal"
typedef struct {
    struct station stationInfo;
    //vector
    tRentType2 * rentInfo;
} tStationType2;

typedef struct bikeRentingCDT{
     tStationType1* station1;
     tStationType2* station2;
} bikeRentingCDT;