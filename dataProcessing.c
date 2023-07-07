/******************************************************************************
 *
 * @file    dataProcessing.c
 *
 * @brief   Manejo de datos y proceso de datos (Back-end).
 *
 * @author  Lucas Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/

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
#define DATE_DELIM "-"

#define UPDATE() strtok(NULL, DELIM_PREFIX)

enum {
    RENTS = 0, STATION
};
enum {
    MON = 1, NYC
};


enum {
    CASUAL, MEMBER
};

#define FILE_RENTS_FORMAT_NYC       "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual"
#define FILE_RENTS_FORMAT_MON       "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member"
#define FILE_STATION_FORMAT_NYC     "station_name;latitude;longitude;id"
#define FILE_STATION_FORMAT_MON     "pk;name;latitude;longitude"

static const char *execMON = "bikeSharingMON";
static const char *execNYC = "bikeSharingNYC";

int validArgumentCount(int argc) {
    if (argc != FILES_COUNT + 1) {
        return DATA_ERROR;
    }
    return SUCCESS;
}

int newFiles(FILE *files[], char *argv[], int count, char *flag) {
    for (int i = 0; i < count; i++) {
        files[i] = fopen(argv[i], flag);
        // Si es NULL no lo pudo leer.
        if (files[i] == NULL) {
            return DATA_ERROR;
        }
    }
    return SUCCESS;
}

int closeFiles(FILE *files[FILES_COUNT]) {
    for (int i = 0; i < FILES_COUNT; i++) {
        if (fclose(files[i]) != 0)
            return DATA_ERROR;
    }
    return SUCCESS;
}


/*
 * @brief Valida que las listas de entrada esten con el formato correcto.
 *
 * @param buff Buffer con tamano para leer linea por linea.
 * @param bikeFile Archivo .csv que contiene la lista de los alquileres.
 * @param stationFile Archivo .csv que contiene la lista de estaciones.
 * @param bikeFormat Se utiliza para validar el formato de la listas de bikes.
 * @param stationFormat Se utiliza para validar el formato de la lista de stations.
 *
 */
static int validFilesFormat(char buff[], FILE *file[FILES_COUNT], char *fileFormat[FILES_COUNT]) {
    for (int i = 0; i < FILES_COUNT; i++) {
        // Si no tiene header (.csv) retorna error.
        if (fgets(buff, BUFF_SIZE, file[i]) == NULL) {
            return DATA_ERROR;
        }

        // Si no tiene el formato correcto retorna error.
        if (strncmp(fileFormat[i], buff, strlen(fileFormat[i])) != 0) {
            return DATA_ERROR;
        }
    }
    return SUCCESS;
}

/*
 * @brief Compara el nombre del ejecutable con la constante correcta del nombre
 * @returns TRUE si son iguales FALSE si no.
 */
static int compareExec(const char *execName, const char *fileName) {
    if (strncmp(execName, fileName + COMMAND_PREFIX, strlen(execName)) == 0) {
        return TRUE;
    }
    return FALSE;
}

/*
 * @brief Obtiene los formatos segun el nombre del ejecutable.
 *
 * @param argv Nombre del ejecutable.
 * @param format Variable de almacemamiento de formatos.
 * @returns Tipo de archivo.
 */
static int getArgumentFormat(char *argv, char *format[FILES_COUNT]) {
    if (compareExec(execMON, argv)) {
        format[RENTS] = FILE_RENTS_FORMAT_MON;
        format[STATION] = FILE_STATION_FORMAT_MON;
        return MON;
    } else if (compareExec(execNYC, argv)) {
        format[RENTS] = FILE_RENTS_FORMAT_NYC;
        format[STATION] = FILE_STATION_FORMAT_NYC;
        return NYC;
    }
    return DATA_ERROR;
}

/*
 * @brief Obtiene el campo del mes
 *
 * @param token String acotado de la fecha.
 * @returns el mes como entero.
 */
static int getMonth(char *token) {

    token = strchr(token, '-') + 1;
    strtok(token, DATE_DELIM);
    return atoi(token);
}

int putDataToADT(bikeSharingADT bs, FILE *file[FILES_COUNT], char *argv) {

    char buff[BUFF_SIZE], *format[FILES_COUNT], *token;
    int valid, type;

    /*
     <* Inicializamos variables del archivo stations<CITY>.csv
     */
    char *stationName;
    int id;

    /*
     * Inicializamos variables del archivo bikes<CITY>.csv
     */
    char isMember;
    size_t idStart, idEnd;
    int month;

    /*
     * Valida el tipo de ejecutable y carga el formato adecuado a la variable.
     */
    type = getArgumentFormat(argv, format);

    if (!validFilesFormat(buff, file, format)) {
        return DATA_ERROR;
    }

    /*
     * Analizo el archivo de station linea por linea, guardando en el buffer cada linea (hasta terminar el archivo) Luego, guardo en firstField el primer campo hasta el delimitador, y en lastField el ultimo campo a partir del ultimo delimitador.
     *
     * Segun el tipo de archivos (MON/NYC) paso los campos intercambiados para agregar la estacion, ya que estan definidos de forma invertida.
     *
     * Guardo en el TAD el tipo de estructura que voy a utilizar.
     */
    if (type == MON) {

        /*
         * Carga de datos al ADT desde file[STATION]
         */
        while (fgets(buff, BUFF_SIZE, file[STATION]) != NULL) {
            token = strtok(buff, DELIM_PREFIX);
            id = atoi(token);
            stationName = UPDATE();
            valid = addStation(bs, stationName, id);
            if (!valid) {
                return DATA_ERROR;
            }
        }

        sortStationsById(bs);   // Ordena las estaciones y realloquea el vector


        /*
         * Carga de datos al ADT desde file[RENTS]
         */
        while (fgets(buff, BUFF_SIZE, file[RENTS]) != NULL) {

            token = strtok(buff, DELIM_PREFIX);
            char *auxMonth = token;

            /* Esta linea significa saltear al siguiente campo. */
            token = UPDATE();

            idStart = atol(token);
            /*
             * Se saltean campos inecesarios
             */
            token = UPDATE(); // aca vale end_Date, como no nos sirve, la salteamos
            token = UPDATE();

            idEnd = atol(
                    token); // en este momento token vale el id de donde termina
            token = UPDATE();

            isMember = atoi(token);
            month = getMonth(auxMonth);
            valid = addRent(bs, month, idStart, idEnd, isMember);
            if (!valid) {
                return DATA_ERROR;
            }
        }
    }

    if (type == NYC) {

        /*
         * Carga de datos al ADT desde file[STATION]
         */
        while (fgets(buff, BUFF_SIZE, file[STATION]) != NULL) {
            token = strtok(buff, DELIM_PREFIX);
            stationName = token;
            token = UPDATE();
            token = UPDATE();
            token = UPDATE();
            id = atoi(token);
            valid = addStation(bs, stationName, id);
            if (!valid) {
                return DATA_ERROR;
            }
        }

        sortStationsById(bs);

        /*
         * Carga de datos al ADT desde file[RENTS]
         */
        while (fgets(buff, BUFF_SIZE, file[RENTS]) != NULL) {
            token = strtok(buff, DELIM_PREFIX);
            char *auxMonth = token;
            token = UPDATE();
            idStart = atol(token);
            token = UPDATE();
            token = UPDATE();
            idEnd = atol(token);
            token = UPDATE();
            token = UPDATE();
            isMember = strncmp("member", token, strlen("member")) == 0
                       ? MEMBER : CASUAL;
            month = getMonth(auxMonth);
            valid = addRent(bs, month, idStart, idEnd, isMember);
            if (!valid) {
                return DATA_ERROR;
            }
        }
    }

    return SUCCESS;
}

