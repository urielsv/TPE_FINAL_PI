#ifndef __bikesharingadt_h_
#define __bikesharingadt_h_

typedef struct bikeSharingCDT * bikeSharingADT;


/*
 * Todas los prototipos estan incompletos, faltan args.
 */
bikeSharingADT newBikeSharingADT(int (*compare)(char* source, char* target));
void freeBikeSharing(void);

// Type1: estilo "New York"
int addStationTypeList(void);

// Type2: estilo "Montreal"
int addStationTypeArray(void);

int addSharingTypeList(bikeSharingADT br);
int addSharingTypeVector(bikeSharingADT br);

#endif
