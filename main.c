/******************************************************************************
 *
 * @file    main.c
 *
 * @brief   Ejecucion del programa y creacion de consultas.
 *
 * @author  Lucas Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/

#include "dataProcessing.h"
#include "dataFront.h"
#include "htmlTable.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE       64
#define FILES_COUNT     2
#define QUERIES_COUNT   3

#define FILE_NAME       0

#define OK              1
#define ERROR           (-1)

enum {
    QUERY1 = 0, QUERY2, QUERY3
};

enum months {
    JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

/*
 * @brief     Guarda en un archivo .csv y .html la informacion de la consulta dada
 *            por la cantidad total de rentas (viajes) por miembros de esa estacion.
 *
 * @param     bs ADT que contiene los datos a consultar.
 * @param     query1 Archivo donde se colocara la informacion de la consulta (.csv)
 * @param     table1 Archivo donde se colocara la informacion de la consulta (.html)
 *
 * @returns   Estado de la query.
 */
int loadQuery1(bikeSharingADT bs, FILE *query1, htmlTable table1);

/*
 * @brief     Guarda en un archivo .csv y .html la informacion de la consulta dada
 *            por la cantidad total de viajes que se realizaron desde EstacionA
 *            hacia la EstacionB y viseversa (de EstacionB a EstacionA).
 *
 * @param     bs ADT que contiene los datos a consultar.
 * @param     query2 Archivo donde se colocara la informacion de la consulta (.csv)
 * @param     table2 Archivo donde se colocara la informacion de la consulta (.html)
 *
 * @returns   Estado de la query.
 */
int loadQuery2(bikeSharingADT bs, FILE *query2, htmlTable table2);

/*
 * @brief     Guarda en un archivo .csv y .html la informacion de la consulta dada
 *            la cantidad total de viajes iniciados por cada mes del anio de cada
 *            estacion.
 *
 * @param     bs ADT que contiene los datos a consultar.
 * @param     query3 Archivo donde se colocara la informacion de la consulta (.csv)
 * @param     table3 Archivo donde se colocara la informacion de la consulta (.html)
 *
 * @returns   Estado de la query.
 */
int loadQuery3(bikeSharingADT bs, FILE *query3, htmlTable table3);


int main(int argc, char *argv[]) {
    /*
     * Antes de comenzar la ejecucion del programa se validan que los argumentos
     * del ejecutable sean correctos.
     */
    validateArguments(argc, argv);

    /*
    * Manejo de de archivos (apertura y creacion)
    */
    FILE *files[FILES_COUNT];
    createFiles(files, argv + 1, FILES_COUNT, "r");

    FILE *queries[QUERIES_COUNT];
    char *queryNames[QUERIES_COUNT] = {
      "query1.csv",
      "query2.csv",
      "query3.csv",
    };

    createFiles(queries, queryNames, QUERIES_COUNT, "w");
    htmlTable table1 = newTable("query1.html", 2,
                                "Station", "StartedTrips");
    htmlTable table2 = newTable("query2.html", 4,
                                "StationA", "StationB", "Trips A->B", "Trips B->A");
    htmlTable table3 = newTable("query3.html", 13,
                                "J", "F", "M", "A", "M", "J", "J", "A", "S", "O", "N", "D", "Station");

    /*
     * Inicializo ADT.
     */
    bikeSharingADT bikeSharing = newBikeSharingADT();

    /*
     * Los datos de los .csv proporcionados se cargan en el ADT.
     */
    loadDataToADT(bikeSharing, files, argv[FILE_NAME]);

    /*
     * Se cargan las consultas a partir de los datos almacenados en bikeSharing.
     */
    validateQuery(loadQuery1(bikeSharing, queries[QUERY1], table1));
    validateQuery(loadQuery2(bikeSharing, queries[QUERY2], table2));
    validateQuery(loadQuery3(bikeSharing, queries[QUERY3], table3));


    /*
     * Libera la memoria utilizada por bikeSharing.
     */
    freeBikeSharing(bikeSharing);

    /*
     * Cerrar los archivos que fueron abiertos.
     */
    closeFiles(files);
    closeHTMLTable(table1);
    closeHTMLTable(table2);
    closeHTMLTable(table3);

    puts("The program has finished with no errors.");
    return 0;
}

static char* integerToString(size_t num, char str[]) {
    snprintf(str, BUFF_SIZE,"%ld", num);
    return str;
}

int loadQuery1(bikeSharingADT bs, FILE *query1, htmlTable table1) {
    sortStationsByRent(bs); // Sortea por cantidad de viajes
    fprintf(query1, "Station;StartedTrips\n");

    size_t total;
    char *stationName;

    for (int i = 0; i < getSize(bs); i++) {
        total = getTotalMemberRents(bs, i);
        stationName = getStationName(bs, i);

        int res = fprintf(query1, "%s;%ld\n", stationName, total);

        char aux[BUFF_SIZE];
        addHTMLRow(table1, stationName, integerToString(total, aux));

        free(stationName);

        if (res < 0) {
            return ERROR;
        }
    }

    return OK;
}

int loadQuery2(bikeSharingADT bs, FILE *query2, htmlTable table2) {
    sortStationsByAlpha(bs);
    fprintf(query2, "StationA;StationB;Trips A->B;Trips B->A\n");

    for (size_t i = 0; i < getSize(bs); i++) {
        char *stationA = getStationName(bs, i);
        for (size_t j = 0; j < getSize(bs); j++) {
            if (i != j) {

                size_t total = getTotalRentsBetweenStations(bs, i, j);
                size_t totalReverse = getTotalRentsBetweenStations(bs, j, i);
                char *stationB = getStationName(bs, j);

                int res = fprintf(query2, "%s;%s;%ld;%ld\n", stationA, stationB, total, totalReverse);

                char aux[BUFF_SIZE][2];
                addHTMLRow(table2, stationA, stationB,
                           integerToString(total, aux[0]),
                           integerToString(totalReverse, aux[1])
                           );

                free(stationB);
                if (res < 0) {
                    return ERROR;
                }
            }
        }
        free(stationA);
    }

    return OK;
}

int loadQuery3(bikeSharingADT bs, FILE *query3, htmlTable table3){

    fprintf(query3, "J;F;M;A;M;J;J;A;S;O;N;D;Station\n");
    for(size_t i = 0; i < getSize(bs); i++ ){
        int * months = calloc(13, sizeof(int));
        getRentsByMonth(bs, i, months);
        char monthsAux[BUFF_SIZE][12];

        for(int j = 1; j < 13; j++){
            fprintf(query3, "%d;", months[j]);
            integerToString(months[j], monthsAux[j]);
        }

        char* stationName = getStationName(bs, i);
        int res = fprintf(query3,"%s\n", stationName);
        addHTMLRow(table3,
                      monthsAux[JAN],
                      monthsAux[FEB],
                      monthsAux[APR],
                      monthsAux[MAR],
                      monthsAux[MAY],
                      monthsAux[JUN],
                      monthsAux[JUL],
                      monthsAux[AUG],
                      monthsAux[SEP],
                      monthsAux[OCT],
                      monthsAux[NOV],
                      monthsAux[DEC],
                      stationName
                   );

        if (res < 0) {
            return ERROR;
        }
        free(stationName);
        free(months);
    }
    return OK;
}
