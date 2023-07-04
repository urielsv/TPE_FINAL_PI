#ifndef __bikesharingadt_h_
#define __bikesharingadt_h_

typedef struct bikeSharingCDT * bikeSharingADT;


/*
 * Todas los prototipos estan incompletos, faltan args.
 */
bikeSharingADT newBikeSharingADT(void);

// Type1: estilo "New York"
int addStationId(bikeSharingADT bs, int id, int type);
int addStationName(bikeSharingADT bs, char* name, int type);

//se fijan si existe el id xD y lo agrega si no esta
int idExist(bikeSharingADT bs, int id, int type);
unsigned int getId(bikeSharingADT bs, unsigned int id);
void freeBikeSharing(bikeSharingADT bs);

#endif

