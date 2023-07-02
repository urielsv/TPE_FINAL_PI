#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TRUE    1
#define FALSE   !TRUE
#define QUERIES_COUNT 2

// Valida cantidad de argumentos (2 queries, renting y station)
static void validateArgumentCount(int argc)
{
    if (argc < 1) {
        fprintf(stderr, "main: no queries specified.");
        exit(1);
    }

    if (argc > 2) {
        fprintf(stderr, "main: invalid amount of queries.");
        exit(1);
    }

}

static void validateQuery(char buff[], int buffSize, FILE** query, char* queryFormat)
{
    if (fgets(buff, buffSize, *query) == NULL) {
        fprintf(stderr, "main: query format not specified.");
        exit(1);
    }

    if (strncmp(queryFormat, buff, strlen(queryFormat)) != 0) {
        fprintf(stderr, "main: invalid query format.");
        exit(1);
    }
}

// en el buffer se guarda la primera linea de bikeStation.
void validateQueriesFormat(char buff[], int buffSize, FILE** bikeQuery, FILE** stationQuery,
                          char* bikeFormat, char* stationFormat)
{
    // Valido formato de queries.
    validateQuery(buff, buffSize, bikeQuery, bikeFormat);
    validateQuery(buff, buffSize, stationQuery, stationFormat);
}