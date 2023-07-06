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
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#define BUFF_SIZE   256
#define FILES_COUNT 2
#define QUERIES 3
#define OK 1
#define ERROR (-1)

enum {
    QUERY1 = 0, QUERY2, QUERY3
};

enum {
    FILE_NAME = 0, FILE1, FILE2
};

enum {
    BIKES = 0, STATION
};


int loadQuery1(bikeSharingADT bs, FILE * query1);
int loadQuery2(bikeSharingADT bs, FILE * query2);
int loadQuery3(bikeSharingADT bs, FILE * query3);

int main(int argc, char *argv[]) {
    // Valido que el ejecutable tenga el formato correcto.
    validateArguments(argc, argv);


    FILE* files[FILES_COUNT];
    createFiles(files, argv+1, "r");

    // Creo mis queries.
    FILE* queries[QUERIES];
    char* queryNames[QUERIES*2] = {
        "query1.csv",
        "query2.csv",
        "query3.csv",
        "query1.html",
        "query2.html",
        "query3.html"
    };
    createFiles(queries, queryNames, "w");

    // Inicializo mi ADT.
    bikeSharingADT bikeSharing = newBikeSharingADT();

    // Cargo data de .csv's a mi ADT.
    loadDataToADT(bikeSharing, files, argv[FILE_NAME]);

    loadQuery1(bikeSharing, queries[QUERY1]);
//    loadQuery2(bikeSharing, queries[QUERY2]);
//    loadQuery3(bikeSharing, queries[QUERY3]);


    // Libero los recursos utilizados por mi ADT.
    freeBikeSharing(bikeSharing);
    puts("Memoria liberada.");
    closeFiles(files);
    puts("Fin de ejecucion.");
    return 0;
}

/*
 * Donde cada línea del archivo csv de salida contenga, separados por “;” el nombre de la
 * estación y la cantidad total de viajes iniciados en esa estación por usuarios miembros.
 * La información debe listarse ordenada en forma descendente por cantidad total de viajes y a igualdad de viajes desempatar alfabéticamente por nombre
 * de la estación.
 */
int loadQuery1(bikeSharingADT bs, FILE * query1){
    sortStationsByRent(bs); // Sortea por cantidad de viajes y elimina los espacion notUsed
    fprintf(query1, "Station;StartedTrips\n");
       size_t total = 0;
       char* stationName;
       for(int i = 0; i < getSize(bs); i++) {
         total = getTotalMemberRents(bs, i);
         stationName = getStationName(bs, i);
         if (total !=-1) {
           int res = fprintf(query1, "%s;%li\n", stationName, total);
             free(stationName);
           if (res < 0){
             return ERROR;
           }
         }
       }


    return OK;
}

int loadQuery2(bikeSharingADT bs, FILE * query2){
    //sortByAlpha(bs,)
}