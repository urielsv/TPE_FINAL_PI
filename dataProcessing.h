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
 * @brief Valida que las listas de entrada esten con el formato correcto.
 *
 * @param buff Buffer con tamano para leer linea por linea.
 * @param buffSize Tamanio de buffer.
 * @param bikeFile Archivo .csv que contiene la lista de los alquileres.
 * @param stationFile Archivo .csv que contiene la lista de estaciones.
 * @param bikeFormat Se utiliza para validar el formato de la listas de bikes.
 * @param stationFormat Se utiliza para validar el formato de la lista de stations.
 *
 */
int validFilesFormat(char buff[], int buffSize, FILE* file[], char* format[]);

/*
 * @brief Obtiene los formatos segun el nombre del ejecutable.
 *
 * @param argv Nombre del ejecutable.
 * @param format Variable de almacemamiento de formatos.
 *
 */
int getArgumentFormat(char* argv, char* format[]);

int putDataToADT(bikeSharingADT adt, FILE* file[], char* format[], char* argv);


#endif
