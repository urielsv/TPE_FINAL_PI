#ifndef __bikesharingadt_h_
#define __bikesharingadt_h_

#include <stdio.h>
typedef struct bikeSharingCDT *bikeSharingADT;

/*
 * CONSTRUCTOR
 */
bikeSharingADT newBikeSharingADT(void);

/*
 * FUNCIONES EXTRAS
 */
int addStation(bikeSharingADT bs, char *stationName, size_t id);
int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char rideableType, char isMember);


/*
 * GETTERS
 */
size_t getId(bikeSharingADT bs, size_t id);
size_t getCountId(bikeSharingADT bs);
int getType(bikeSharingADT bs);

/*
 * SETTERS
 */
void setType(bikeSharingADT bs, int type);

/*
 * @brief Libera todos los recursos utilizados por el ADT.
 */
void freeBikeSharing(bikeSharingADT bs);

void printName(bikeSharingADT bs, size_t id);

#endif
