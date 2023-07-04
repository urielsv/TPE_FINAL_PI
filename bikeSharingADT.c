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
    size_t sizeRentList; // cantidad de nodos
} tStationArray;

/*
 * ESTRUCTURA ADT
 */
typedef struct bikeSharingCDT {
    tStationList *stationList; // NYC, lista de stations con lista de rents
    tStationArray *stationArray; // MON, vector de stations con lista de rents
    size_t sizeList; // Cantidad de stations
    size_t sizeArray; // Cantidad de stations
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
        return SUCCESS;
    }

    if (getType(bs) == LIST){
        tStationList *newNode = malloc(sizeof(tStationList));

        newNode->stationInfo.stationName = stationName;
        newNode->stationInfo.id = id;
        newNode->next = NULL;

        if (newNode == NULL) {
            return ERROR;
        }

        if (bs->stationList == NULL) {
            bs->stationList = newNode;
        } else {
            tStationList *current = bs->stationList;
            newNode->next = current;
            bs->stationList = newNode;
        }

        bs->sizeList++;
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
        newRent->next = NULL;

        tStationArray *station = &(bs->stationArray[startId]);

        if (station->rentList == NULL) {
            station->rentList = newRent;
        } else {
            tRentList *current = station->rentList;
            newRent->next = current;
            station->rentList = newRent;
        }
//        printf("month:%d startId: %zu endId:%zu isMember:%d \n", station->rentList->startMonth, startId, station->rentList->endId, station->rentList->isMember);
        station->sizeRentList++;
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

/*
 * SETTERS
 */
void setType(bikeSharingADT bs, int type) {
    bs->type = type;
}

// Free
void freeBikeSharing(bikeSharingADT bs) {
    if (getType(bs) == ARRAY) {

        tRentList* current = bs->stationArray->rentList;
        int i = 0;
        while (current != NULL) {
            tRentList* temp = current;
            current = current->next;
            free(temp);
            printf("%d", i++);
        }

        free(bs->stationArray);
    }
/*
    if (getType(bs) == LIST) {

    }
*/
    free(bs);
    printf("freed :)");
}
