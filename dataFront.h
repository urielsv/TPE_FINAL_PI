/******************************************************************************
 *
 * @file    bikeSharingADT.c
 *
 * @brief   Manejo del Front-end.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/

#ifndef __datafront_h_
#define __datafront_h_
#include <stdio.h>
#include "bikeSharingADT.h"

/*
 * @brief   Retorna mensaje de error y termina el programa
 *
 * @param   errorStream Origen del error.
 * @param   errorText Mensaje de error.
 */
void pError(const char* errorStream, const char* errorText);

/*
 * @brief   Valida que los argumentos del programa sean validos.
 *
 * @param   argc Cantidad de argumentos.
 * @param   argv Nombre de cada argumento.
 */
void validateArguments(int argc, char* argv[]);

void createFiles(FILE** files, char* argv[], int count, char* flag);

/*
 * @brief   Verifica que la carga de datos al ADT sea correcta.
 *
 */
void loadDataToADT(bikeSharingADT bikeSharing, FILE**files, char* argv);

void validateQuery(int status);
#endif
