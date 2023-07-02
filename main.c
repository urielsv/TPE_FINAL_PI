#include "dataProcessing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


#define BUFF_SIZE   256
#define QUERY_BIKES_FORMAT_1    "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual" // NY
#define QUERY_BIKES_FORMAT_2    "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member"// MON
#define QUERY_STATION_FORMAT_LIST   "station_name;latitude;longitude;id" // NY
#define QUERY_STATION_FORMAT_ARRAY  "pk;name;latitude;longitude" // MON

enum {QUERY1=0, QUERY2, QUERY3};
enum {FILE1=1, FILE2};

int main(int argc, char * argv[])
{
    validateArgumentCount(argc);

    FILE* bikeQuery = fopen(argv[FILE1], "r");
    FILE* stationQuery = fopen(argv[FILE2], "r");

    char buff[BUFF_SIZE];
    // para queries tipo "NY" (habria que ver como hacer con makefile
    // para poder pasarle los defines de los formatos.
    validateQueriesFormat(buff, BUFF_SIZE, bikeQuery, stationQuery,
                          QUERY_BIKES_FORMAT_1, QUERY_STATION_FORMAT_LIST);

    // Sera funcion de dataProcessing.
    processDataToADT();


    return 0;
}