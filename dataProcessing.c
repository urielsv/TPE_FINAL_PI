/******************************************************************************
 *
 * @file    dataProcessing.c
 *
 * @brief   Manejo de datos y proceso de datos (Back-end).
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bikeSharingADT.h"

#define BUFF_SIZE   256
#define COMMAND_PREFIX  2 // "./" prefix de un ejecutable
#define TRUE    1
#define FALSE   !TRUE
#define FILES_COUNT 2
#define SUCCESS 1
#define DATA_ERROR !SUCCESS
#define DELIM_PREFIX ";"
#define DATE_DELIM "-"
#define UPDATE()  strtok(NULL, DELIM_PREFIX)

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

int newFiles(FILE **files, char *argv[], int count, char *flag) {
    for (int i = 0; i < count; i++) {
        files[i] = fopen(argv[i], flag);
        // Si es NULL no lo pudo leer.
        if (files[i] == NULL) {
            return DATA_ERROR;
        }
    }
    return SUCCESS;
}

int closeFiles(FILE **files) {
    for (int i = 0; i < FILES_COUNT; i++) {
        if (fclose(files[i]) != 0)
            return DATA_ERROR;
    }
    return SUCCESS;
}

/*
 * @brief     Valida que las listas de entrada esten con el formato correcto.
 *
 * @param     buff Buffer con tamano para leer linea por linea.
 * @param     bikeFile Archivo .csv que contiene la lista de los alquileres.
 * @param     stationFile Archivo .csv que contiene la lista de estaciones.
 * @param     bikeFormat Se utiliza para validar el formato de la listas de bikes.
 * @param     stationFormat Se utiliza para validar el formato de la lista de stations.
 *
 */
static int validFilesFormat(char buff[], FILE **file, char *fileFormat[FILES_COUNT]) {
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
 * @brief     Compara el nombre del ejecutable con la constante correcta del nombre.
 * @returns   TRUE si son iguales FALSE si no.
 */
static int compareExec(const char *execName, const char *fileName) {
    if (strncmp(execName, fileName + COMMAND_PREFIX, strlen(execName)) == 0) {
        return TRUE;
    }
    return FALSE;
}

/*
 * @brief     Obtiene los formatos segun el nombre del ejecutable.
 *
 * @param     argv Nombre del ejecutable.
 * @param     format Variable de almacemamiento de formatos.
 * @returns   Tipo de archivo.
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
 * @brief     Obtiene el campo del mes
 *
 * @param     token String acotado de la fecha.
 * @returns   Mes como integer.
 */
static int getMonth(char *token) {

    token = strchr(token, '-') + 1;
    strtok(token, DATE_DELIM);
    return atoi(token);
}


/*
 * @brief     Cargo los datos a partir de .csv al ADT.
 *
 *            Valido para las funciones: loadStationsMON, loadStationsNYC,
 *            loadRentsMON y loadRentsNYC.
 *
 * @param     bs ADT utilizado para la carga de datos.
 * @param     file  Archivo (.csv) que contiene los datos a obtener.
 *
 * @returns   Estado de funcion (si se pudo obtener los datos).
 */
static int loadStationsMON(bikeSharingADT bs, FILE* file) {
    char buff[BUFF_SIZE], *token, *stationName;
    size_t id;
    int valid;

    while (fgets(buff, BUFF_SIZE, file) != NULL) {
        token = strtok(buff, DELIM_PREFIX);
        id = atol(token);
        stationName = UPDATE();
        valid = addStation(bs, stationName, id);
        if (!valid) {
            return DATA_ERROR;
        }
    }

    sortStationsById(bs);
    return SUCCESS;
}

static int loadRentsMON(bikeSharingADT bs, FILE *file) {
    char buff[BUFF_SIZE], *token, *auxMonth, isMember;
    size_t idStart, idEnd;
    int valid, month;

    while (fgets(buff, BUFF_SIZE, file) != NULL) {

        token = strtok(buff, DELIM_PREFIX);
        auxMonth = token;
        /* Esta linea significa saltear al siguiente campo. */
        token = UPDATE();

        idStart = atol(token);
        /* Se saltean campos inecesarios */
        token = UPDATE(); // aca vale end_Date, como no nos sirve, la salteamos
        token = UPDATE();

        idEnd = atol(token); // en este momento token vale el id de donde termina
        token = UPDATE();

        isMember = atoi(token);
        month = getMonth(auxMonth);
        valid = addRent(bs, month, idStart, idEnd, isMember);
        if (!valid) {
            return DATA_ERROR;
        }
    }

    return SUCCESS;
}

static int loadStationsNYC(bikeSharingADT bs, FILE *file) {
    char buff[BUFF_SIZE], *token, *stationName;
    int valid;
    size_t id;

    while (fgets(buff, BUFF_SIZE, file) != NULL) {
        token = strtok(buff, DELIM_PREFIX);
        stationName = token;
        token = UPDATE();
        token = UPDATE();
        token = UPDATE();
        id = atol(token);
        valid = addStation(bs, stationName, id);
        if (!valid) {
            return DATA_ERROR;
        }
    }

    sortStationsById(bs);

    return SUCCESS;
}

static int loadRentsNYC(bikeSharingADT bs, FILE *file) {
    char buff[BUFF_SIZE], *token, *auxMonth, isMember;
    size_t idStart, idEnd;
    int valid, month;

    while (fgets(buff, BUFF_SIZE, file) != NULL) {
        token = strtok(buff, DELIM_PREFIX);
        auxMonth = token;
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

    return SUCCESS;
}

int putDataToADT(bikeSharingADT bs, FILE *file[FILES_COUNT], char *argv) {

    char buff[BUFF_SIZE], *format[FILES_COUNT];
    int valid, type;

    /*
     * Valida el tipo de ejecutable y carga el formato adecuado a la variable.
     */
    type = getArgumentFormat(argv, format);

    if (!validFilesFormat(buff, file, format)) {
        return DATA_ERROR;
    }

    /*
     * A partir del tipo de .csv cargo los datos.
     * Primero, cargo los datos de las estaciones al ADT, si este proceso
     * fue valido (no errores) entonces procede a cargar los datos de las
     * rentas de estas estaciones en el ADT.
     *
     * En cualquier caso de error retorna DATA_ERROR.
     */
    if (type == MON) {
        valid = loadStationsMON(bs, file[STATION]);

        if (!valid) {
            return DATA_ERROR;
        }

        valid = loadRentsMON(bs, file[RENTS]);

        if (!valid) {
            return DATA_ERROR;
        }

    } else if (type == NYC) {
        valid = loadStationsNYC(bs, file[STATION]);
        if (!valid) {
            return DATA_ERROR;
        }

        valid = loadRentsNYC(bs, file[RENTS]);

        if (!valid) {
            return DATA_ERROR;
        }

    } else {
        return DATA_ERROR;
    }

    return SUCCESS;
}

