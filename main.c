#include "dataProcessing.h"
#include "dataFront.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define BUFF_SIZE   256
#define INPUT_FILES 2

enum {QUERY1=0, QUERY2, QUERY3};
enum {FILE_NAME=0, FILE1, FILE2};
enum {BIKES=0, STATION};


int main(int argc, char * argv[])
{
    // argv[0] me da el formato
    validateArguments(argc, argv);

    // Obtengo el formato segun el tipo (NYC/MON)
    char* format[INPUT_FILES];

    // Hay que mandarlo al error handler del front (para printear)
    getArgumentFormat(argv[FILE_NAME], format);

    FILE* bikeFile = fopen(argv[FILE1], "r");
    FILE* stationFile = fopen(argv[FILE2], "r");

    char buff[BUFF_SIZE];

    // Hay que mandarlo al error handler del front (para printear)
    validFilesFormat(buff, BUFF_SIZE, &bikeFile, &stationFile,
                          format[BIKES], format[STATION]);

    // Sera funcion de dataProcessing.
    // processDataToADT();
    return 0;
}
