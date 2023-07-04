#include "dataProcessing.h"
#include "dataFront.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define BUFF_SIZE   256
#define FILES_COUNT 2

enum {QUERY1=0, QUERY2, QUERY3};
enum {FILE_NAME=0, FILE1, FILE2};
enum {BIKES=0, STATION};


int main(int argc, char * argv[])
{
    // argv[0] me da el formato
    validateArguments(argc, argv);

    // Obtengo el formato segun el tipo (NYC/MON)
    char* format[FILES_COUNT];

    // Hay que mandarlo al error handler del front (para printear)
    getArgumentFormat(argv[FILE_NAME], format);

    FILE* bikeFile = fopen(argv[FILE1], "r");
    FILE* stationFile = fopen(argv[FILE2], "r");

    FILE* files[FILES_COUNT] = {bikeFile, stationFile};

    char buff[BUFF_SIZE];

    // Hay que mandarlo al error handler del front (para printear)
    validFilesFormat(buff, BUFF_SIZE, &files, format);
    // Sera funcion de dataProcessing.
    // processDataToADT();

    bikeSharingADT bikeSharing = newBikeSharingADT();

    int status = putDataToADT(bikeSharing, files, format, argv[FILE_NAME]);
    printf("%d", status);

    return 0;
}
