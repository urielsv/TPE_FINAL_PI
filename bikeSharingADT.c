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

enum {
    LIST=0, ARRAY
};

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
 * @struct  tStationList
 *
 * @brief   Estructura de estacion para tipo "List"
 *
 ******************************************************************************/
typedef struct stationList{
    tStation stationInfo;
    tRentList *rentList;
    struct stationList* next;
} tStationList;

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
    int isUsed;
} tStationArray;

/******************************************************************************
 *
 * @struct  bikeSharingCDT
 *
 * @brief   Atributos del CDT.
 *
 ******************************************************************************/
typedef struct bikeSharingCDT {
    tStationList *stationList; // NYC, lista de stations con lista de rents
    tStationArray *stationArray; // MON, vector de stations con lista de rents
    size_t sizeArray; // Cantidad alojada de station.
    size_t stationCount; // Cantidad de ids (stations)
    int type; // list = 0, array = 1
} bikeSharingCDT;


/******************************************************************************
 *
 * @category    CONSTRUCTOR FUNCTION
 *
 ******************************************************************************/
bikeSharingADT newBikeSharingADT(void) {
    bikeSharingADT bs = calloc(1, sizeof(struct bikeSharingCDT));
    bs->type = UNDEFINED;
    return bs;
}

/******************************************************************************
 *
 * @category    FUNCTIONS
 *
 ******************************************************************************/
static void memCheck(void *allocMem) {
    if (errno == ENOMEM)  {
        exit(1);
    }
}

static char* stringCopy(const char* str) {
  char* copy = malloc((strlen(str)+1) * sizeof(char));
  memCheck(copy);

  strcpy(copy, str);
  copy[strlen(str)] = 0;
  return copy;
}

static void addStationArray(bikeSharingADT bs, char* stationName, size_t id) {
    if (id > bs->sizeArray) {
        size_t newCapacity = id + BLOCK;

        bs->stationArray = realloc(bs->stationArray,
                                   newCapacity * sizeof(tStationArray));
        memCheck(bs->stationArray);
        for (size_t i = bs->sizeArray; i < newCapacity; i++){
            bs->stationArray[i].stationInfo.stationName = NULL;
            bs->stationArray[i].rentList = NULL;
            bs->stationArray[i].isUsed = 0;
            bs->stationArray[i].stationInfo.totalRents = 0;
            bs->stationArray[i].stationInfo.totalMemberRents = 0;
        }

        bs->sizeArray = newCapacity;
    }

    bs->stationArray[id].stationInfo.stationName = stringCopy(stationName);
    bs->stationArray[id].stationInfo.id = id;
    bs->stationArray[id].isUsed = 1;
    bs->stationCount++;
}

static void addStationList(bikeSharingADT bs, char* stationName, size_t id) {
    tStationList* newStation = malloc(sizeof(tStationList));
    memCheck(newStation);

    newStation->stationInfo.stationName = stringCopy(stationName);
    newStation->stationInfo.id = id;
    newStation->stationInfo.totalRents = 0;
    newStation->stationInfo.totalMemberRents = 0;
    newStation->rentList = NULL;


    tStationList* current = bs->stationList;
    tStationList* previous = NULL;

    while (current != NULL && strcmp(current->stationInfo.stationName, stationName) < 0) {
            previous = current;
            current = current->next;
    }

    if (previous == NULL) {
        // La nueva estacion debe ser el primer nodo de la lista
        newStation->next = bs->stationList;
        bs->stationList = newStation;
    } else {
        // La nueva estacion debe ser insertada entre previous y current
        previous->next = newStation;
        newStation->next = current;
    }
    //printf("encontrado\n");
    bs->stationCount++;
}


int addStation(bikeSharingADT bs, char *stationName, size_t id) {
    if (getType(bs) == ARRAY) {
        addStationArray(bs, stationName, id);
        return SUCCESS;
    }

    if (getType(bs) == LIST) {
        addStationList(bs, stationName, id);
        return SUCCESS;
    }
    return ERROR;
}

static int addRentArray(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char isMember) {
    if (startId >= bs->sizeArray || bs->stationArray == NULL) {
        return ERROR; // el id no existe
    }
    if (bs->stationArray[startId].isUsed) {

        tRentList *newRent = malloc(sizeof(tRentList));
        memCheck(newRent);

        newRent->startMonth = startMonth;
        newRent->endId = endId;
        newRent->isMember = isMember;
        newRent->next = NULL;

        tRentList* aux = bs->stationArray[startId].rentList;
        bs->stationArray[startId].rentList = newRent;
        bs->stationArray[startId].rentList->next = aux;
        bs->stationArray[startId].stationInfo.totalRents++;
        bs->stationArray[startId].stationInfo.totalMemberRents += (int) isMember;
        return SUCCESS;
    }


    return ERROR;

}

static tStationList * findStation(tStationList * list, size_t id){
    if(list == NULL) {
        return NULL;
    }
    tStationList *current = list;
    while(current != NULL) {
        if (current->stationInfo.id == id) {
            //printf("STATION NAME: %s\t", current->stationInfo.stationName);
            return current;
        }
        current = current->next;
    }

    return NULL;
}

static int addRentList(bikeSharingADT bs, int startMonth, size_t startId,
                       size_t endId, char isMember) {

    tStationList *currStation = findStation(bs->stationList, startId);
//    tStationList *currStation = bs->stationList;
    tRentList *newRent = malloc(sizeof(tRentList));
    memCheck(newRent);

    newRent->startMonth = startMonth;
    newRent->endId = endId;
    newRent->next =NULL;
    newRent->isMember = isMember;

    tRentList * aux = currStation->rentList;
    currStation->rentList = newRent;
    currStation->rentList->next=aux;
    currStation->stationInfo.totalMemberRents += (int) isMember;
    currStation->stationInfo.totalRents++;

    return SUCCESS;
}

int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char isMember) {
    int valid;
    if (getType(bs) == ARRAY) {
        valid = addRentArray(bs, startMonth, startId, endId, isMember);
        return valid;
    }
    if (getType(bs) == LIST) {
        valid = addRentList(bs, startMonth, startId, endId, isMember);
        return valid;
    }
    return ERROR;
}


/******************************************************************************
 *
 * @category    GETTER FUNCTIONS
 *
 ******************************************************************************/
int getType(bikeSharingADT bs) {
    return bs->type;
}

size_t getId(bikeSharingADT bs, size_t id) {
    return bs->stationArray[id].isUsed ? bs->stationArray[id].stationInfo.id : 0;
}

size_t getStationCount(bikeSharingADT bs) {
    return bs->stationCount;
}

char* getStationName(bikeSharingADT bs, size_t id) {
    if (getType(bs) == ARRAY && bs->stationArray[id].isUsed) {
        return stringCopy(bs->stationArray[id].stationInfo.stationName);
    }

    if (getType(bs) == LIST) {
        tStationList* currStation = findStation(bs->stationList, id);
        if (currStation == NULL) {
            return NULL;
        }
        char* copy = stringCopy(currStation->stationInfo.stationName);
        return copy;
    }

    return NULL;
}

size_t getTotalRents(bikeSharingADT bs, size_t id) {
    if (getType(bs) == ARRAY && bs->stationArray[id].isUsed) {
        return bs->stationArray[id].stationInfo.totalRents;
    }
    if (getType(bs) == LIST) {
        tStationList* currStation = findStation(bs->stationList, id);
        return currStation->stationInfo.totalRents;
    }
    return UNDEFINED;
}

size_t getTotalMemberRents(bikeSharingADT bs, size_t id) {
    if (getType(bs) == ARRAY && bs->stationArray[id].isUsed) {
        return bs->stationArray[id].stationInfo.totalMemberRents;
    }
    if (getType(bs) == LIST) {
        tStationList* currStation = findStation(bs->stationList, id);

        // Si es un id que no existe
        if (currStation == NULL) {
            return UNDEFINED;
        }

        return currStation->stationInfo.totalMemberRents;
    }
    return UNDEFINED;
}

size_t getSize(bikeSharingADT bs) {
    if (getType(bs) ==  ARRAY) {
        return bs->sizeArray;
    }

    /*
     * Si es lista entonces no hay nodos "sin utilidad" entonces devuelvo la
     * cantidad de estaciones que hay.
     */
    if (getType(bs) == LIST) {
        return bs->stationCount;
    }
}

char isUsed(bikeSharingADT bs, size_t id) {
    if (getType(bs) == ARRAY) {
        bs->stationArray[id].isUsed;
    }
    if (getType(bs) == LIST) {
        tStationList* currStation = findStation(bs->stationList, id);
        return currStation != NULL;
    }
    return UNDEFINED;
}
/******************************************************************************
 *
 * @category    SETTER FUNCTIONS
 *
 ******************************************************************************/
void setType(bikeSharingADT bs, int type) {
    bs->type = type;
}

/******************************************************************************
 *
 * @category    FREE MEMORY
 *
 ******************************************************************************/
static void freeRecRents(tRentList* rents) {
    if (rents == NULL)
        return;
    freeRecRents(rents->next);
    free(rents);
}

static void freeRecList(tStationList * list){
    if (list == NULL)
        return;

    freeRecRents(list->rentList);
    freeRecList(list->next);
    free(list->stationInfo.stationName);
    free(list);
}

void freeBikeSharing(bikeSharingADT bs) {

    if (bs->type == ARRAY) {
        for (int i = 0; i < bs->sizeArray; i++) {
              free(bs->stationArray[i].stationInfo.stationName);
              freeRecRents(bs->stationArray[i].rentList);
        }
        free(bs->stationArray);
    }

    if(bs->type == LIST) {

        freeRecList(bs->stationList);
    }

    free(bs);
}

/******************************************************************************
 *
 * @category    FUNCIONES EXTRA
 *
 ******************************************************************************/
void printList(bikeSharingADT bs) {
    tStationList * current = bs->stationList;
    int i=0;
    while(current != NULL){
//        printf(" [%u] Current: %u, %s\n has %zu rents", i, current->stationInfo.id, current->stationInfo.stationName, current->sizeRentList);
        current = current->next;
        i++;
    }
}

static int stationsByRents(const void * a, const void * b) {
    const tStationArray *stationA = (const tStationArray *)a;
    const tStationArray *stationB = (const tStationArray *)b;

    if (stationA->stationInfo.totalMemberRents == stationB->stationInfo.totalMemberRents)
        return strcmp(stationA->stationInfo.stationName, stationB->stationInfo.stationName);
    else if (stationA->stationInfo.totalMemberRents < stationB->stationInfo.totalMemberRents)
        return 1;
    else if (stationA->stationInfo.totalMemberRents > stationB->stationInfo.totalMemberRents)
        return -1;

    return 0;
}

static void clearNotUsedStationsArray(bikeSharingADT bs) {

    int i, j=0;
    for(i =0 ; i < bs->sizeArray; i++) {
        if(bs->stationArray[i].isUsed) {
              bs->stationArray[j++] =bs->stationArray[i];
        }
    }
    bs->stationArray = realloc(bs->stationArray, j*sizeof(tStationArray));
    bs->sizeArray = j;
}

void sortStationsByRent(bikeSharingADT bs) {
    if (getType(bs) == ARRAY) {
        clearNotUsedStationsArray(bs);

        qsort(bs->stationArray, bs->sizeArray, sizeof(tStationArray),
              stationsByRents);
    }

    if (getType(bs) == LIST) {

    }
}

static int stringCompare(const void* a, const void* b) {
    return strcmp(a, b);
}

void sortByAlpha(bikeSharingADT bs) {
        if (getType(bs) == ARRAY) {
              // por si no se llama el primer sort.
              clearNotUsedStationsArray(bs);

              qsort(bs->stationArray, bs->sizeArray, sizeof(tStationArray),stringCompare);
        }
}

