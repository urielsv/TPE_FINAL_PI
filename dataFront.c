/******************************************************************************
 *
 * @file    dataFront.c
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

#include "dataFront.h"
#include "dataProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME 0
#define FILES_COUNT 2

void pError(const char* errorStream, const char* errorText)
{
    fprintf(stderr, "%s: %s\n", errorStream, errorText);
    exit(1);
}

void validateArguments(int argc, char* argv[]) {
    if (!validArgumentCount(argc)) {
        pError("main", "invalid argument count.");
    }
}

void createFiles(FILE* files[FILES_COUNT], char* argv[], char* flag) {
    if (strcmp(flag, "r") != 0 && strcmp(flag, "w") != 0) {
        pError("file(s):", "Not a valid read/write flag.");
    }
    int valid = newFiles(files, argv, flag);
    if (!valid) {
        pError("file(s):", "Permission denied.");
    }
    printf("Files have been loaded successfully.\n");
}

void loadDataToADT(bikeSharingADT bs, FILE* files[FILES_COUNT], char* argv) {
    int valid = putDataToADT(bs, files, argv);

    if (!valid) {
        pError("main", "Failed to load data to ADT.");
    }

    printf("main: Data has been loaded correctly.\n");
}

//void loadQueries(FILE* queries[], int count) {
//    for (int i = 0; i < count; i++) {
//
//    }
//}
