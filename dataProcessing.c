#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MON_EXEC    "bikeRentingMON" // newyork
#define NYC_EXEC    "bikeRentingNYC" // newcanada
#define COMMAND_PREFIX  2
#define TRUE    1
#define FALSE   !TRUE
#define QUERIES_COUNT 2

#define QUERY_BIKES_FORMAT_NYC   "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual"
#define QUERY_STATION_FORMAT_NYC   "station_name;latitude;longitude;id"
#define QUERY_BIKES_FORMAT_MON    "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member"
#define QUERY_STATION_FORMAT_MON  "pk;name;latitude;longitude"

enum {BIKES=0, STATION};
static const char* execMON = "bikeSharingMON";
static const char* execNYC = "bikeSharingMON";

void getArgumentFormat(char* argv, char* format[QUERIES_COUNT])
{
    // idea aux: comprar unicamente la 'M' con la 'N'
    if (strncmp(execMON, argv+COMMAND_PREFIX, strlen(execMON)) == 0) {
        format[BIKES] = QUERY_BIKES_FORMAT_MON;
        format[STATION] = QUERY_STATION_FORMAT_MON;
        return;
    }

    // Otra forma sin strncmp
    if (strcmp(NYC_EXEC, argv+COMMAND_PREFIX) == 0) {
        format[BIKES] = QUERY_BIKES_FORMAT_NYC;
        format[STATION] = QUERY_STATION_FORMAT_NYC;
        return;
    }

    fprintf(stderr, "main: invalid queries format.");
    exit(1);
}

// Valida cantidad de argumentos (2 queries, renting y station)
void validateArgumentCount(int argc)
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
