#include "dataProcessing.h"
#include "dataFront.h"
#include <stdio.h>
#include <assert.h>

#define BUFF_SIZE   256
#define FILES_COUNT 2

enum {
    QUERY1 = 0, QUERY2, QUERY3
};

enum {
    FILE_NAME = 0, FILE1, FILE2
};

enum {
    BIKES = 0, STATION
};


int main(int argc, char *argv[]) {
    // Valido que el ejecutable tenga el formato correcto.
    validateArguments(argc, argv);

    FILE *bikeFile = fopen(argv[FILE1], "r");
    FILE *stationFile = fopen(argv[FILE2], "r");

    // esto ya se valida en el back.
    if (stationFile == NULL || bikeFile == NULL) {
        // Handle file opening error here
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }


    FILE *files[FILES_COUNT] = {bikeFile, stationFile};

    // Inicializo mi ADT.
    bikeSharingADT bikeSharing = newBikeSharingADT();

    // Cargo data de .csv's a mi ADT.
    loadDataToADT(bikeSharing, files, argv[FILE_NAME]);


//    addStation(bikeSharing, "xd", 1);
//    addStation(bikeSharing, "xd", 2);
//    addStation(bikeSharing, "xd", 3);
//
//
//    addRent(bikeSharing, 1, 1, 4, 1, 1);
//    addRent(bikeSharing, 1, 1, 5, 1, 1);
    // Libero los recursos utilizados por mi ADT.

    freeBikeSharing(bikeSharing);

    //printf("%d",getCountId(bikeSharing));

    printf("main: OK y solido");


    fclose(stationFile);
    fclose(bikeFile);
    return 0;
}
