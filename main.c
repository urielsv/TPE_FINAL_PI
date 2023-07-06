/******************************************************************************
 *
 * @file    main.c
 *
 * @brief   Ejecucion del programa.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/
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


    FILE* files[FILES_COUNT];
    createFiles(files, argv);

    // Inicializo mi ADT.
    bikeSharingADT bikeSharing = newBikeSharingADT();

    // Cargo data de .csv's a mi ADT.
    loadDataToADT(bikeSharing, files, argv[FILE_NAME]);

    //printList(bikeSharing);

    // Libero los recursos utilizados por mi ADT.
    freeBikeSharing(bikeSharing);
    puts("Mem liberada.");
    closeFiles(files);
    puts("Fin de ejecucion.");
    return 0;
}
