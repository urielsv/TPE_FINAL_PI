#include "dataProcessing.h"
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
    validateArgumentCount(argc);

    // Obtengo el formato segun el tipo (NYC/MON)
    char* format[INPUT_FILES];
    getArgumentFormat(argv[FILE_NAME], format);

    FILE* bikeQuery = fopen(argv[FILE1], "r");
    FILE* stationQuery = fopen(argv[FILE2], "r");

    char buff[BUFF_SIZE];
    validateQueriesFormat(buff, BUFF_SIZE, &bikeQuery, &stationQuery,
                          format[BIKES], format[STATION]);

    // Sera funcion de dataProcessing.
    // processDataToADT();
    return 0;
}
