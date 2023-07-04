#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bikeSharingADT.h"

#define BUFF_SIZE   256
#define COMMAND_PREFIX  2 // "./$COMMAND"
#define TRUE    1
#define FALSE   !TRUE
#define FILES_COUNT 2
#define SUCCESS 1
#define DATA_ERROR !SUCCESS
#define DELIM_PREFIX ";"
#define UPDATE strtok(NULL, DELIM_PREFIX) // macro para pasar al siguiente token

enum {BIKES=0, STATION, TYPE};
enum {MON, NYC};

static const char* fileBikesFormatNYC = "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual";
static const char* fileBikesFormatMON = "station_name;latitude;longitude;id";
static const char* fileStationFormatNYC = "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member";
static const char* fileStationFormatMON = "pk;name;latitude;longitude";
static const char* execMON = "bikeSharingMON";
static const char* execNYC = "bikeSharingNYC";

// Valida cantidad de argumentos (2 queries, renting y station)
int validArgumentCount(int argc)
{
    if (argc != FILES_COUNT+1) {
        return DATA_ERROR;
    }

    return SUCCESS;
}


// AUX: en el buffer se guarda la primera linea de bikeStation.
int validFilesFormat(char buff[], int buffSize, FILE** file[FILES_COUNT], char* fileFormat[FILES_COUNT])
{
    for (int i = 0; i < FILES_COUNT; i++) {
        if (fgets(buff, buffSize, *file[i]) == NULL
            || strncmp(fileFormat[i], buff, strlen(fileFormat[i])) != 0) {
            return DATA_ERROR;
        }
    }
    return SUCCESS;
}

static int copyFormat(char* argv, char* format[FILES_COUNT], const char* execName)
{
    if (strncmp(execName, argv+COMMAND_PREFIX, strlen(execName)) == 0) {
        format[BIKES] = strcpy(format[BIKES], fileBikesFormatMON);
        format[STATION] = strcpy(format[STATION], fileStationFormatMON);
        return SUCCESS;
    }
    return DATA_ERROR;
}

int getArgumentFormat(char* argv, char* format[FILES_COUNT])
{
    int validNameMON, validNameNYC;
    validNameMON = copyFormat(argv, format, execMON);
    validNameNYC = copyFormat(argv, format, execNYC);

    if (!validNameMON || !validNameNYC) {
        return DATA_ERROR;
    }

    return SUCCESS;

}

static int getType(char* argv) {
    if (compareExec(execMON, argv))
            return MON;
    if (compareExec(execNYC, argv))
            return NYC;
}

int putDataToADT(bikeSharingADT adt, FILE* file[FILES_COUNT], char* format[FILES_COUNT], char* argv)
{
    int id;
    char *stationName;
    char buff[BUFF_SIZE], *token;


    if (!validFilesFormat(buff, BUFF_SIZE, &file, format)) {
        return DATA_ERROR;
    }

    // if es tipo "MON"
    int type = getType(argv);

    if (type == MON) {
        //leo las lineas del archivo hasta el final, guardo la linea en buff hasta BUFF_SIZE caracteres.
       // while (fgets(buff, BUFF_SIZE, file[STATION]) != NULL) {
            token = strtok(buff, DELIM_PREFIX);
            id = atoi(token);

            // addStationId add if not exists
            if (!addStationId(adt, id, type)) {
                printf("%d", getId(adt, id));
                token = UPDATE;
                // stationName = token;
                //addStationName(adt, stationName);
            }

        //}
    }
/*
    if (type == NYC) {

    }


*/
    return SUCCESS;
}
