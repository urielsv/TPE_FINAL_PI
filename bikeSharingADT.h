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
int addStation(bikeSharingADT bs, char *name, unsigned int id);
int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char rideableType, char isMember);


/*
 * GETTERS
 */
int getId(bikeSharingADT bs, unsigned int id);
int getType(bikeSharingADT bs);

/*
 * SETTERS
 */
void setType(bikeSharingADT bs, int type);

/*
 * @brief Libera todos los recursos utilizados por el ADT.
 */
void freeBikeSharing(bikeSharingADT bs);

#endif
