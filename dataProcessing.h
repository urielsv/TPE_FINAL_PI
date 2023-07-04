#ifndef __dataprocessing_h_
#define __dataprocessing_h_
#include <stdio.h>
#include "bikeSharingADT.h"


enum {ERR_INVALID_FILE_COUNT=1,
        ERR_NULL_FILE_FORMAT,
        ERR_FILE_FORMAT,
        ERR_COPY_FAILED
};

/*
 * @brief Valida la cantidad de argumentos en el ejecutable.
 *
 * @param argc Cantidad de archivos.
 */
int validArgumentCount(int argc);

/*
 * @brief Guarda en ADT los datos obtenidos a partir de las listas.
 *
 * Valida que los formatos de los archivos sean correctos, a partir de una correcta
 * definicion del nombre del ejecutable. Recorre el archivo hasta el final, linea por linea
 * guardando en un buffer, de tamanio arbitrario cada linea de lectura.
 *
 * @param bikeSharing el ADT que maneja operaciones de los datos.
 * @param file Distintos archivos con lista de datos.
 * @param argv Nombre del archivo ejecutable.
 */
int putDataToADT(bikeSharingADT bikeSharing, FILE* file[], char* argv);


#endif
