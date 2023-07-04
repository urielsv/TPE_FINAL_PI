#ifndef __datafront_h_
#define __datafront_h_
#include <stdio.h>

/*
 * @brief Retorna mensaje de error y termina el programa
 *
 * @param errorStream Origen del error.
 * @param errorText Mensaje de error.
 */
void pError(const char* errorStream, const char* errorText);

/*
 * @brief Valida que los argumentos del programa sean validos.
 *
 * @param argc Cantidad de argumentos.
 * @param argv Nombre de cada argumento.
 */
void validateArguments(int argc, char* argv[]);

#endif
