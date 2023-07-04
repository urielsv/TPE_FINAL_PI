#include "bikeSharingADT.h"
#include <stdlib.h>
#include <errno.h>

#define SUCCESS 1
#define FOUND 1
#define NOT_FOUND !FOUND
#define BLOCK 150
// ARRAY es como "MON"
// LIST es como "NYC"
enum {ARRAY, LIST};

// Sharing tipo "New York"
typedef struct rent1 {
    struct rent* a;
    char rideable_type;
    struct rent1* next;
} tRent1;

// Sharing tipo "Montreal"
// idem a struct rent

struct rent {
    char* start; // date or place
    char* end; // same
    size_t startId;
    size_t endId;
    char isMember;
};

struct station {
    char* station_name;
    double latitude;
    double longitude;
    unsigned int id;
};

// Station tipo "New York" (lista)
typedef struct {
    struct station stationInfo;
    tRent1 * list;
} tStationList;

// Station tipo "Montreal" (vector)
typedef struct {
    struct station stationInfo;
    struct rent* rentInfo;
} tStationArray;

// Guardar de forma ordenada (alfab) o despues sortear?
typedef struct bikeSharingCDT {
     tStationList* stationList;
     tStationArray* stationArray;
     size_t dimList;
     size_t dimArray;
     size_t sizeArray;
} bikeSharingCDT;

bikeSharingADT newBikeSharingADT(void)
{
    bikeSharingADT bs = calloc(1, sizeof(struct bikeSharingCDT));
    return bs;
}

static int belongsArray(tStationArray* station, size_t dim, int id)
{
    for (int i = 0; i < dim; i++) {
        if (station->stationInfo.id == id) {
            return i;
        }
    }
    return -1;
}

static int addIdArray(bikeSharingADT bs, size_t dim, int id)
{
    if (id > dim) {
        bs->stationArray=realloc(bs->stationArray, (id + BLOCK) * sizeof(tStationArray));
        if (errno == ENOMEM) {
            return ENOMEM;
        }
        bs->sizeArray = dim+BLOCK;
    }

    bs->stationArray[id].stationInfo.id = id;
    return SUCCESS;
}


int addStationId(bikeSharingADT bs, int id, int type)
{
    if (type == ARRAY) {
        // Si no existia lo agrega y retorna que no estaba
        if (!belongsArray(bs->stationArray, bs->dimArray, id)){
            //addIdArray(bs, bs->dimArray, id);
            return NOT_FOUND;
        }
        return FOUND;
    }
/*
    if (type == LIST){

    }


    */

    return SUCCESS;
}

unsigned int getId(bikeSharingADT bs, unsigned int id)
{
    return bs->stationArray[id].stationInfo.id;
}

static void freeRentList(tRent1* rentList) {
    if (rentList == NULL) {
        return;
    }

    freeRentList(rentList->next);
    free(rentList);
}

void freeBikeSharing(bikeSharingADT bs) {
    /*if (bs == NULL) {
        return;
    }

    for (size_t i = 0; i < bs->sizeArray; i++) {
        free(bs->stationArray[i].rentInfo);
    }

    free(bs->stationArray);

    for (size_t i = 0; i < bs->dimList; i++) {
        freeRentList(bs->stationList[i].list);
    }

    free(bs->stationList);
    free(bs);*/
    free(bs);
}
