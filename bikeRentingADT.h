#ifndef BIKE_RENTING_ADT
#define BIKE_RENTING_ADT

typedef struct bikeRentingCDT * bikeRentingADT;


/*
 * Todas los prototipos estan incompletos, faltan args.
 */

bikeRentingADT newBikeRentingADT(int (*compare)(char* source, char* target));
void freeBikeRenting();

// Type1: estilo "New York"
int addStationTypeList();

// Type2: estilo "Montreal"
int addStationTypeArray();

int addRentingTypeList(bikeRentingADT br);
int addRentingTypeVector(bikeRentingADT br);

#endif
