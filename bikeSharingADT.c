#include "bikeSharingADT.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SUCCESS 1
#define ERROR !SUCCESS
#define FOUND 1
#define NOT_FOUND !FOUND
#define UNDEFINED (-1)
#define BLOCK 150

enum {
    LIST=0, ARRAY
};

typedef struct rentList {
    char *start; // date or place
    char *end; // same
    size_t startId;
    size_t endId;
    char rideableType;
    char isMember;
    struct rentList *next;
} tRentList;

typedef struct station {
    char *stationName;
    unsigned int id;
} tStation;

// Station tipo "New York" (lista)
typedef struct stationList{
    tStation stationInfo;
    tRentList *rentList;
    size_t sizeRentList; // cantidad de nodos
    struct stationList* next;
} tStationList;

// Station tipo "Montreal" (vector)
typedef struct {
    tStation stationInfo;
    tRentList *rentList;
    size_t sizeRentList; // cantidad de nodos
} tStationArray;

// Guardar de forma ordenada (alfab) o despues sortear?
typedef struct bikeSharingCDT {
    tStationList *stationList; // NYC, lista de stations con lista de rents
    tStationArray *stationArray; // MON, vector de stations con lista de rents
    size_t sizeList; // Cantidad de stations
    size_t sizeArray; // Cantidad de stations
    int type; // list = 0, array = 1
} bikeSharingCDT;


bikeSharingADT newBikeSharingADT(void) {
    bikeSharingADT bs = calloc(1, sizeof(struct bikeSharingCDT));
    bs->type = UNDEFINED;
    return bs;
}
//
//static int belongsIdArray(bikeSharingADT bs, int id) {
//    int dim = bs->sizeArray;
//    for (int i = 0; i < dim; i++) {
//        if (bs->stationArray->stationInfo.id == id) {
//            return i;
//        }
//    }
//    return -1;
//}


int addStation(bikeSharingADT bs, char *stationName, unsigned int id) {

    if (getType(bs) == ARRAY) {
        if (id >= bs->sizeArray) {

            size_t newCapacity = id + BLOCK;
            tStationArray *auxArray = realloc(bs->stationArray, newCapacity * sizeof(tStationArray));
            if (errno == ENOMEM) {
                return ENOMEM;
            }

            bs->stationArray = auxArray;
            bs->sizeArray = newCapacity;
        }

        bs->stationArray[id].stationInfo.stationName = stationName;
        bs->stationArray[id].stationInfo.id = id;
        printf("%s, %d\n", bs->stationArray[id].stationInfo.stationName, bs->stationArray[id].stationInfo.id);
        return SUCCESS;
    }
/*
    if (getType(bs) == LIST){
        return SUCCESS;
    }
    */
    return ERROR;
}

void setType(bikeSharingADT bs, int type) {
    bs->type = type;
}

int getType(bikeSharingADT bs) {
    return bs->type;
}

unsigned int getId(bikeSharingADT bs, unsigned int id) {
    return bs->stationArray[id].stationInfo.id;
}


// Free memoria heap
void freeBikeSharing(bikeSharingADT bs) {
    if (getType(bs) == ARRAY) {
       // free(bs->stationArray->rentArray);
        free(bs->stationArray);
    }
/*
    if (getType(bs) == LIST) {

    }
*/
    free(bs);
}
