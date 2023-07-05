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

/*
 * RENT
 */
typedef struct rentList {
    int startMonth; // date
    size_t endId;
    char rideableType;
    char isMember;
    struct rentList *next;
} tRentList;

/*
 * STATIONS
 */
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
    int isUsed;
    size_t sizeRentList; // cantidad de nodos
} tStationArray;

/*
 * ESTRUCTURA ADT
 */
typedef struct bikeSharingCDT {
//    tStationList *stationList; // NYC, lista de stations con lista de rents
    tStationArray *stationArray; // MON, vector de stations con lista de rents
//    size_t sizeList; // Cantidad de stations
    size_t sizeArray; // Cantidad de stations (alojadas)
    size_t countIds; // Cantidad de ids
    int type; // list = 0, array = 1
} bikeSharingCDT;


/*
 * CONSTRUCTOR
 */
bikeSharingADT newBikeSharingADT(void) {
    bikeSharingADT bs = calloc(1, sizeof(struct bikeSharingCDT));
    bs->type = UNDEFINED;
    return bs;
}

/*
 * FUNCIONES
 */
static void memCheck(void *allocMem) {
    if (allocMem == NULL)  {
        exit(1);
    }
}
int addStation(bikeSharingADT bs, char *stationName, size_t id) {
    if (getType(bs) == ARRAY) {

        if (id > bs->sizeArray) {
              tStationArray *auxArray = realloc(bs->stationArray, (id + BLOCK) * sizeof(tStationArray));
              memCheck(auxArray);
              bs->stationArray = auxArray;
              bs-?
              bs->countIds = id; // id es le max
        }
    }
}
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
        bs->stationArray[id].isUsed = 1;
        printf("AGREGADA STATION: id:%u\n", bs->stationArray[id].stationInfo.id);

        return SUCCESS;
    }

    return ERROR;
}

int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char rideableType, char isMember) {

    if (getType(bs) == ARRAY) {
        if (startId >= bs->sizeArray || bs->stationArray == NULL) {
            return ERROR; // el id no existe
        }

        tRentList *newRent = malloc(sizeof(tRentList));
        if (errno == ENOMEM) {
            return ENOMEM;
        }

        newRent->startMonth = startMonth;
        newRent->endId = endId;
        newRent->rideableType = rideableType;
        newRent->isMember = isMember;
        newRent->next = bs->stationArray[startId].rentList;
        bs->stationArray[startId].rentList = newRent;

        bs->stationArray[startId].sizeRentList++;
         // printf("AGREGADO RENT: size %zd endId %zd\n", bs->stationArray[startId].sizeRentList, bs->stationArray[startId].rentList->endId);
        return SUCCESS;
    }

    /*
    if (getType(bs) == LIST){
        return SUCCESS;
    }
    */
    return ERROR;
}


/*
 * GETTERS
 */
int getType(bikeSharingADT bs) {
    return bs->type;
}

size_t getId(bikeSharingADT bs, size_t id) {
    return bs->stationArray[id].isUsed;
}
/*
 * SETTERS
 */
void setType(bikeSharingADT bs, int type) {
    bs->type = type;
}

/*
 * FREE
 */
static void freeRecRents(tRentList* rents) {
    if (rents == NULL)
        return;
    freeRecRents(rents->next);
    free(rents);
}
