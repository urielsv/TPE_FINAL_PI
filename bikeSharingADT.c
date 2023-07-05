#include "bikeSharingADT.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

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
    if (errno == ENOMEM)  {
        exit(1);
    }
}

int addStation(bikeSharingADT bs, char *stationName, size_t id) {
    if (getType(bs) == ARRAY) {

        if (id > bs->sizeArray) {
            size_t newCapacity = id + BLOCK;

            bs->stationArray = realloc(bs->stationArray, newCapacity * sizeof(tStationArray));
            memCheck(bs->stationArray);
            for (size_t i = bs->sizeArray; i < newCapacity; i++){
                bs->stationArray[i].stationInfo.stationName = NULL;
                bs->stationArray[i].rentList = NULL;
                bs->stationArray[i].isUsed = 0;
                bs->stationArray[i].sizeRentList = 0;
            }

            bs->sizeArray = newCapacity;
        } else {
            bs->sizeArray++;
        }

        bs->stationArray[id].stationInfo.stationName = stationName;
        bs->stationArray[id].stationInfo.id = id;
        bs->stationArray[id].isUsed = 1;
        bs->countIds++;

//        printf("AGREGADA STATION: id:%u used:%d\n", bs->stationArray[id].stationInfo.id, bs->stationArray[id].isUsed);
        return SUCCESS;
    }
    return ERROR;
}
//int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char rideableType, char isMember) {
//
//}


int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char rideableType, char isMember) {

    if (getType(bs) == ARRAY) {
        if (startId >= bs->sizeArray || bs->stationArray == NULL) {
            return ERROR; // el id no existe
        }

        tRentList *newRent = malloc(sizeof(tRentList));
        if (errno == ENOMEM) {
            return ENOMEM;
        }

        if (bs->stationArray[startId].isUsed) {
            newRent->startMonth = startMonth;
            newRent->endId = endId;
            newRent->rideableType = rideableType;
            newRent->isMember = isMember;
            newRent->next = bs->stationArray[startId].rentList;
            bs->stationArray[startId].rentList = newRent;
            bs->stationArray[startId].sizeRentList++;
        }

//        printf("AGREGADO RENT: id: %d\t\t\tsize: %zd\t\t\t\tendId: %zd\n",
//             bs->stationArray[startId].stationInfo.id,
//             bs->stationArray[startId].sizeRentList,
//             bs->stationArray[startId].rentList->endId);
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
    return bs->stationArray[id].isUsed ? bs->stationArray[id].stationInfo.id : 0;
}

size_t getCountId(bikeSharingADT bs) {
    return bs->countIds;
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

void freeBikeSharing(bikeSharingADT bs) {

    if (bs->type == ARRAY) {
        for (int i = 0; i < bs->countIds; i++) {
            if (bs->stationArray[i].isUsed)
              freeRecRents(bs->stationArray[i].rentList);
        }
        free(bs->stationArray);
    }

    free(bs);
}
