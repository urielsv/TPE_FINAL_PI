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
static const char* fileBikesFormatMON = "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member";
static const char* fileStationFormatNYC = "station_name;latitude;longitude;id";
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

int validFilesFormat(char buff[], int buffSize, FILE* file[FILES_COUNT], char* fileFormat[FILES_COUNT])
{
    for (int i = 0; i < FILES_COUNT; i++) {
        if (fgets(buff, buffSize, file[i]) == NULL
            || strncmp(fileFormat[i], buff, strlen(fileFormat[i])) != 0) {
            return SUCCESS;
        }
    }
    return DATA_ERROR;
}

/*
 * @brief Compara el nombre del ejecutable con la constante correcta del nombre
 * @returns TRUE si son iguales FALSE si no.
 */
static int compareExec(const char * execName, const char* fileName){
    if (strncmp(execName, fileName+COMMAND_PREFIX, strlen(execName)) == 0) {
        return TRUE;
    }
    return FALSE;
}

int getArgumentFormat(char* argv, char* format[FILES_COUNT])
{
    if (compareExec(execMON, argv)) {
        format[BIKES] = fileBikesFormatMON;
        format[STATION] = fileStationFormatMON;
        return SUCCESS;
    } else if (compareExec(execNYC, argv)){
        format[BIKES] = fileBikesFormatNYC;
        format[STATION] = fileStationFormatNYC;
        return SUCCESS;
    }
    return DATA_ERROR;
}

static int getType(char* argv) {
    if (compareExec(execMON, argv))
            return MON;
    if (compareExec(execNYC, argv))
            return NYC;
    return -1; // temp
}

int putDataToADT(bikeSharingADT adt, FILE* file[FILES_COUNT], char* format[FILES_COUNT], char* argv)
{
    int id;
    //char *stationName;
    char buff[BUFF_SIZE], *token;


   if (!validFilesFormat(buff, BUFF_SIZE, file, format)) {
        return DATA_ERROR;
   }

   int type = getType(argv);

   if (type == MON) {
        // Leo las lineas del archivo hasta el final, guardo la linea en buff hasta BUFF_SIZE
        // caracteres.
        while (fgets(buff, BUFF_SIZE, file[STATION]) != NULL) {
            token = strtok(buff, DELIM_PREFIX);
            id = atoi(token);

            // addStationId add if not exists
            //    if (!addStationId(adt, id, type)) {
                printf("id:%d \n", id);
                token = UPDATE;
                // stationName = token;
                //addStationName(adt, stationName);
            //}

        }
   }
/*
    if (type == NYC) {

    }
*/
   return SUCCESS;
}
