#include "bikeSharingADT.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 1
#define ERROR !SUCCESS
#define FOUND 1
#define NOT_FOUND !FOUND
#define UNDEFINED (-1)
#define BLOCK 150


/******************************************************************************
 *
 * @struct  tRentList
 *
 * @brief   Estructura de rentas de tipo "List"
 *
 ******************************************************************************/
typedef struct rentList {
    int startMonth; // date
    size_t endId;
    char isMember;
    struct rentList *next;
} tRentList;

/******************************************************************************
 *
 * @struct  tStation
 *
 * @brief   Estructura de estacion generica.
 *
 ******************************************************************************/
typedef struct station {
    char *stationName;
    unsigned int id;
    size_t totalMemberRents;
    size_t totalRents; // cantidad de nodos equivalente a total usuarios
} tStation;


/******************************************************************************
 *
 * @struct  tStationArray
 *
 * @brief   Estructura de estacion para tipo "Array"
 *
 ******************************************************************************/
typedef struct {
    tStation stationInfo;
    tRentList *rentList;
} tStationArray;

/******************************************************************************
 *
 * @struct  bikeSharingCDT
 *
 * @brief   Atributos del CDT.
 *
 ******************************************************************************/
typedef struct bikeSharingCDT {
    tStationArray *stationArray; // MON, vector de stations con lista de rents
    size_t sizeArray; // Cantidad alojada de station.
    size_t stationCount; // Cantidad de ids (stations)
} bikeSharingCDT;

/******************************************************************************
 *
 * @category    CONSTRUCTOR FUNCTION
 *
 ******************************************************************************/
bikeSharingADT newBikeSharingADT(void) {
    bikeSharingADT bs = calloc(1, sizeof(struct bikeSharingCDT));
    return bs;
}

/******************************************************************************
 *
 * @category    FUNCTIONS
 *
 ******************************************************************************/
static void memCheck(void *allocMem) {
    if (errno == ENOMEM) {
        exit(1);
    }
}

static char *stringCopy(const char *str) {
    char *copy = malloc((strlen(str) + 1) * sizeof(char));
    memCheck(copy);

    strcpy(copy, str);
    copy[strlen(str)] = 0;
    return copy;
}

int addStation(bikeSharingADT bs, char *stationName, size_t id) {

    if (bs->stationCount == bs->sizeArray) {
        size_t newCapacity = bs->sizeArray + BLOCK;

        bs->stationArray = realloc(bs->stationArray,
                                   newCapacity * sizeof(tStationArray));
        memCheck(bs->stationArray);
        bs->sizeArray = newCapacity;
    }
    bs->stationArray[bs->stationCount].rentList = NULL;
    bs->stationArray[bs->stationCount].stationInfo.stationName = stringCopy(stationName);
    bs->stationArray[bs->stationCount].stationInfo.id = id;
    bs->stationArray[bs->stationCount].stationInfo.totalMemberRents = 0;
    bs->stationCount++;

    return SUCCESS;

}

size_t findStation(bikeSharingADT bs, size_t id) {
    size_t low = 0;
    size_t high = bs->stationCount - 1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        size_t currentId = bs->stationArray[mid].stationInfo.id;

        if (currentId == id) {
            return mid;
        } else if (currentId < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return UNDEFINED;
}

int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char isMember) {
    size_t indexStation = findStation(bs, startId);

    tRentList *newRent = malloc(sizeof(tRentList));
    memCheck(newRent);

    newRent->startMonth = startMonth;
    newRent->endId = endId;
    newRent->isMember = isMember;
    newRent->next = NULL;

    tRentList *aux = bs->stationArray[indexStation].rentList;
    bs->stationArray[indexStation].rentList = newRent;
    bs->stationArray[indexStation].rentList->next = aux;
    bs->stationArray[indexStation].stationInfo.totalRents++;
    bs->stationArray[indexStation].stationInfo.totalMemberRents += (int) isMember;

    return SUCCESS;
}

/******************************************************************************
 *
 * @category    GETTER FUNCTIONS
 *
 ******************************************************************************/
size_t getStationCount(bikeSharingADT bs) {
    return bs->stationCount;
}

char *getStationName(bikeSharingADT bs, size_t id) {
    return stringCopy(bs->stationArray[id].stationInfo.stationName);
}

size_t getTotalRents(bikeSharingADT bs, size_t id) {
    return bs->stationArray[id].stationInfo.totalRents;
}

size_t getTotalMemberRents(bikeSharingADT bs, size_t id) {
    return bs->stationArray[id].stationInfo.totalMemberRents;
}

size_t getSize(bikeSharingADT bs) {
    return bs->stationCount;
}

/******************************************************************************
 *
 * @category    SETTER FUNCTIONS
 *
 ******************************************************************************/


/******************************************************************************
 *
 * @category    FREE MEMORY
 *
 ******************************************************************************/
static void freeRecRents(tRentList *rents) {
    if (rents == NULL)
        return;
    freeRecRents(rents->next);
    free(rents);
}

void freeBikeSharing(bikeSharingADT bs) {
    for (size_t i = 0; i < bs->stationCount; i++) {

        if (bs->stationArray[i].rentList != NULL) {
            freeRecRents(bs->stationArray[i].rentList);
        }

        free(bs->stationArray[i].stationInfo.stationName);
    }
    free(bs->stationArray);

    free(bs);
}

/******************************************************************************
 *
 * @category    SORTING FUNCTIONS
 *
 ******************************************************************************/
int compareStationsById(const void *station1, const void *station2) {
    const tStationArray *s1 = (const tStationArray *) station1;
    const tStationArray *s2 = (const tStationArray *) station2;

    if (s1->stationInfo.id < s2->stationInfo.id) {
        return -1;
    } else if (s1->stationInfo.id > s2->stationInfo.id) {
        return 1;
    } else {
        return 0;
    }
}

// Sortea pr id de forma ascendente
void sortStationsById(bikeSharingADT bs) {
    bs->stationArray = realloc(bs->stationArray,
                               bs->stationCount * sizeof(tStationArray));
    memCheck(bs->stationArray);

    qsort(bs->stationArray, bs->stationCount, sizeof(tStationArray), compareStationsById);
}

int compareStationsByRentDescending(const void *station1, const void *station2) {
    const tStationArray *s1 = (const tStationArray *) station1;
    const tStationArray *s2 = (const tStationArray *) station2;

    if (s1->stationInfo.totalMemberRents == s2->stationInfo.totalMemberRents) {
        return strcmp(s1->stationInfo.stationName, s2->stationInfo.stationName);
    }

    if (s1->stationInfo.totalMemberRents > s2->stationInfo.totalMemberRents) {
        return -1;
    } else if (s1->stationInfo.totalMemberRents < s2->stationInfo.totalMemberRents) {
        return 1;
    } else {
        return 0;
    }
}

// Sortea por cantidad de rents (por miembros) de forma descendente
void sortStationsByRent(bikeSharingADT bs) {
    size_t n = bs->stationCount;
    qsort(bs->stationArray, n, sizeof(tStationArray), compareStationsByRentDescending);
}

static int stringCompare(const void *a, const void *b) {
    return strcmp(a, b);
}

// Sortea por nombre de forma ascendente
void sortByAlpha(bikeSharingADT bs) {
    qsort(bs->stationArray, bs->sizeArray, sizeof(tStationArray), stringCompare);

}

/******************************************************************************
 *
 * @category    EXTRA FUNCTIONS
 *
 ******************************************************************************/
void printArray(bikeSharingADT bs) {
    for (int i = 0; i < bs->stationCount; i++) {
        printf("%s\thas %zu rents\n", bs->stationArray[i].stationInfo.stationName,
               bs->stationArray[i].stationInfo.totalRents);
    }
}

void printTotalRents(bikeSharingADT bs, size_t i) {
    printf("%s has %zu rents\n", bs->stationArray[i].stationInfo.stationName, getTotalRents(bs, i));
}

void printRents(bikeSharingADT bs, size_t i) {
    tRentList *aux = bs->stationArray[i].rentList;
    while (aux != NULL) {
        printf("%zu\n", aux->endId);
        aux = aux->next;
    }
}
