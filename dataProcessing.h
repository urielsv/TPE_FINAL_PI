/******************************************************************************
 *
 * @file    dataProcessing.h
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

#ifndef __dataprocessing_h_
#define __dataprocessing_h_

#include <stdio.h>
#include "bikeSharingADT.h"

/*
 * @brief Valida la cantidad de argumentos en el ejecutable.
 *
 * @param argc Cantidad de archivos.
 */
int validArgumentCount(int argc);

/*
 * @brief Guarda en files la informacion de los archivos.
 */
int newFiles(FILE *files[], char *argv[], char *flag);

/*
 * @brief Cierra los archivos previamente abiertos.
 */
int closeFiles(FILE *files[]);

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
int putDataToADT(bikeSharingADT bikeSharing, FILE *file[], char *argv);

void printArray(bikeSharingADT bs);

void printRents(bikeSharingADT bs, size_t id);

#endif
