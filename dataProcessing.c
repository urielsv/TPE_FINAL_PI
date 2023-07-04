#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define COMMAND_PREFIX  2 // "./$COMMAND"
#define TRUE    1
#define FALSE   !TRUE
#define FILES_COUNT 2
#define SUCCESS 1
#define DATA_ERROR !SUCESS

enum {BIKES=0, STATION};

static const char* fileBikesFormatNYC = "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual";
static const char* fileBikesFormatMON = "station_name;latitude;longitude;id";
static const char* fileStationFormatNYC = "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member";
static const char* fileStationFormatMON = "pk;name;latitude;longitude";
static const char* execMON = "bikeSharingMON";
static const char* execNYC = "bikeSharingNYC";

// Valida cantidad de argumentos (2 queries, renting y station)
int validArgumentCount(int argc)
{
    if (argc != FILES_COUNT) {
        return ERR_INVALID_FILE_COUNT;
    }

    return SUCCESS;
}

static int validFile(char buff[], int buffSize, FILE** file, char* fileFormat)
{
    if (fgets(buff, buffSize, *file) == NULL
        || strncmp(fileFormat, buff, strlen(fileFormat)) != 0) {
        return DATA_ERROR;
    }

    return SUCCESS;
}

// AUX: en el buffer se guarda la primera linea de bikeStation.
int validFilesFormat(char buff[], int buffSize, FILE** bikeFile, FILE** stationFile,
                          char* bikeFormat, char* stationFormat)
{
    int validBikeFormat, validStationFormat;
    validBikeFormat = validFile(buff, buffSize, bikeFile, bikeFormat);
    validStationFormat = validFile(buff, buffSize, stationFile, stationFormat);

    if (!validBikeFormat && !validStationFormat) {
        return DATA_ERROR;
    }
    return SUCESS;
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
