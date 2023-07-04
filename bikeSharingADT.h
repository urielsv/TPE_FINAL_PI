#ifndef __bikesharingadt_h_
#define __bikesharingadt_h_

typedef struct bikeSharingCDT *bikeSharingADT;


/*
 * Todas los prototipos estan incompletos, faltan args.
 */
bikeSharingADT newBikeSharingADT(void);

// Type1: estilo "New York"
int addStationId(bikeSharingADT bs, int id);

int addStationName(bikeSharingADT bs, char *name);

//se fijan si existe el id xD y lo agrega si no esta
int idExist(bikeSharingADT bs, int id);

unsigned int getId(bikeSharingADT bs, unsigned int id);

void freeBikeSharing(bikeSharingADT bs);

void setType(bikeSharingADT bs, int type);

int getType(bikeSharingADT bs);

int getStationId(bikeSharingADT bs, int id);

int addStation(bikeSharingADT bs, char *name, unsigned int id);

#endif
