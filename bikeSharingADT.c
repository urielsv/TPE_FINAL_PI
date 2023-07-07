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
 ******************************************************************************/\
typedef struct { // whathe fuck?
    size_t count;
    char* stationName;
    size_t endId;
} tEndIdArray;

typedef struct {
    tStation stationInfo;
    tRentList *rentList;
    tEndIdArray * endIdArray;
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

void reallocateStationsArray(bikeSharingADT bs) {
    bs->stationArray = realloc(bs->stationArray,
                               bs->stationCount * sizeof(tStationArray));
    memCheck(bs->stationArray);

    bs->sizeArray = bs->stationCount;

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

static long int findStation(bikeSharingADT bs, size_t id) {
    long int low = 0;
    long int high = (long int) (bs->stationCount);

    while (low <= high) {
        long int mid = low + (high - low) / 2;
        long int currentId = bs->stationArray[mid].stationInfo.id;
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
   // printf(" findstation en index= %zu\n", indexStation);

    if (indexStation == UNDEFINED) {
      printf("indexStation error\n");
      return ERROR;
    }

    tRentList *newRent = malloc(sizeof(tRentList));
    memCheck(newRent);

    newRent->startMonth = startMonth;
   // printf("%d\n", newRent->startMonth);
    newRent->endId = endId;
    newRent->isMember = isMember;
    newRent->next = NULL;

    tRentList *aux = bs->stationArray[indexStation].rentList;
    bs->stationArray[indexStation].rentList = newRent;
    bs->stationArray[indexStation].rentList->next = aux;
    bs->stationArray[indexStation].stationInfo.totalRents++;
    bs->stationArray[indexStation].stationInfo.totalMemberRents += (int) isMember;

    long int endIndexStation = findStation(bs,endId);
//    if (endIndexStation == UNDEFINED) {
//        printf("%zu endid station error, UNDEFINED %d\n", endIndexStation, (int) UNDEFINED);
//        return ERROR;
//    }
    if (endIndexStation != UNDEFINED)
    bs->stationArray[indexStation].endIdArray[endIndexStation].count++;

//    if(strcmp(bs->stationArray[indexStation].stationInfo.stationName,bs->stationArray[0].stationInfo.stationName) == 0)
//      printf("la station %s tiene %d del end id %d\n", bs->stationArray[indexStation].stationInfo.stationName,bs->stationArray[indexStation].endIdArray[endIndexStation].count, endId);

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
    return bs->sizeArray;
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
        for(int j =0 ; j < bs->stationCount; j++){
            free(bs->stationArray[i].endIdArray[j].stationName);
        }
        free(bs->stationArray[i].endIdArray);
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
    reallocateStationsArray(bs);
    qsort(bs->stationArray, bs->stationCount, sizeof(tStationArray), compareStationsById);
    for (int i = 0; i < bs->stationCount; i++) {
        // buenas vibras y felicidad #positivevibes
        bs->stationArray[i].endIdArray = calloc(bs->stationCount, sizeof(tEndIdArray));
        // copiar los nombres de
        for(int j = 0; j < bs->stationCount; j++) {
            bs->stationArray[i].endIdArray[j].endId = bs->stationArray[i].stationInfo.id;
            bs->stationArray[i].endIdArray[j].stationName =
                stringCopy(bs->stationArray[j].stationInfo.stationName);
        }
    }

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
    qsort(bs->stationArray, bs->sizeArray, sizeof(tStationArray),
          compareStationsByRentDescending);
}

int compareStations(const void *a, const void *b) {
    const tStationArray *stationA = (const tStationArray *)a;
    const tStationArray *stationB = (const tStationArray *)b;

    return strcmp(stationA->stationInfo.stationName, stationB->stationInfo.stationName);
}

static int compareEndIdArray(const void* a, const void* b) {
    const tEndIdArray* arrA = (const tEndIdArray*)a;
    const tEndIdArray* arrB = (const tEndIdArray*)b;
    return strcmp(arrA->stationName, arrB->stationName);
}

// Sortea por nombre de forma alfabetica
void sortStationsByAlpha(bikeSharingADT bs) {
    qsort(bs->stationArray, bs->stationCount,
          sizeof(tStationArray), compareStations);

    // el problema es que sortea las stationsArray pero no sortea el vecetor adentro (endIdArray)
    for (int i = 0; i < bs->stationCount; i++) {
        qsort(bs->stationArray[i].endIdArray, bs->stationCount, sizeof(tEndIdArray), compareEndIdArray);
      }
//        printf("%s[count: %zu]\t%s\n",bs->stationArray[0].stationInfo.stationName,
//               bs->stationArray[0].endIdArray[i].count, bs->stationArray[0].endIdArray[i].stationName);

//    for( int j = 0; j < bs->stationCount; j++) {
//    printf("station: %s, endStation:%s count: %zu\n", bs->stationArray[0].stationInfo.stationName ,
//    bs->stationArray[0].endIdArray[j].stationName,bs->stationArray[i].endIdArray[j].count);
//    }
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

void printEndRentsArray(bikeSharingADT bs, size_t index) {
    for(int i =0; i< bs->sizeArray; i++) {
        printf("%zu\n", bs->stationArray[index].endIdArray[i].count);
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

size_t getTotalRentsBetweenStations(bikeSharingADT bs, size_t startIndex, size_t endIndex) {
    size_t totalRents = bs->stationArray[startIndex].endIdArray[endIndex].count;
    return totalRents;
}

void getRentsByMonth(bikeSharingADT bs, size_t stationIndex, int* monthArray) {
    tRentList *aux = bs->stationArray[stationIndex].rentList;
    while (aux != NULL) {
        monthArray[aux->startMonth]++;
        //printf("%d\t startmonth: %d",monthArray[aux->startMonth],aux->startMonth );
        aux = aux->next;
    }
}
