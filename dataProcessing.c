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

enum {
    BIKES = 0, STATION
};
enum {
    MON = 1, NYC
};

enum {
    LIST, ARRAY
};

#define FILE_BIKES_FORMAT_NYC       "started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual"
#define FILE_BIKES_FORMAT_MON       "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member"
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
        format[BIKES] = FILE_BIKES_FORMAT_MON;
        format[STATION] = FILE_STATION_FORMAT_MON;
        return MON;
    } else if (compareExec(execNYC, argv)) {
        format[BIKES] = FILE_BIKES_FORMAT_NYC;
        format[STATION] = FILE_STATION_FORMAT_NYC;
        return NYC;
    }
    return DATA_ERROR;
}

/*
 * @brief Obtiene a partir de la ultima aparicion del delimitador el ultimo field.
 *
 * @returns Ultimo field del .csv
 */
//static char *getLastField(char buff[]) {
//    // strrchr(buff, ';') me devuelve la ultima aparicion de ";"
//    // El +1 es para saltear el delimitador.
//    return strrchr(buff, (char) DELIM_PREFIX) + 1;
//}

int putDataToADT(bikeSharingADT bs, FILE *file[FILES_COUNT], char *argv) {

    char buff[BUFF_SIZE], *format[FILES_COUNT], *stationName, *id;
    int valid;

    // Valida y "coloca" el formato correcto a format y devuelve el tipo
    int type = getArgumentFormat(argv, format);

    if (!validFilesFormat(buff, file, format)) {
        return DATA_ERROR;
    }

    /*
     * Analizo el archivo de station linea por linea, guardando en el buffer cada linea (hasta terminar el archivo)
     * Luego, guardo en firstField el primer campo hasta el delimitador, y en lastField el ultimo campo a partir del
     * ultimo delimitador.
     *
     * Segun el tipo de archivos (MON/NYC) paso los campos intercambiados para agregar la estacion, ya que estan
     * definidos de forma invertida.
     *
     * Guardo en el TAD el tipo de estructura que voy a utilizar.
     */
    if (type == MON) {
        setType(bs, ARRAY);
        while (fgets(buff, BUFF_SIZE, file[STATION]) != NULL) {
            id = strtok(buff, DELIM_PREFIX);
            stationName = strtok(NULL, DELIM_PREFIX);
            valid = addStation(bs, stationName, atoi(id));
            if (!valid) {
                return DATA_ERROR;
            }
        }

        //file[BIKES]
        //while ()
    }
    return SUCCESS;

/*
        if (type == NYC) {
            setType(bs, LIST);
            addStation(bs, firstField, atoi(lastField));
        }


    while (fgets(buff, BUFF_SIZE, file[BIKES]) != NULL) {
        firstField = strtok(buff, DELIM_PREFIX);
        lastField = getLastField(buff);

        if (type == MON) {
            // addRent
        }
        if (type == NYC) {
            // addRent
        }
    }
*/
    return SUCCESS;
}
