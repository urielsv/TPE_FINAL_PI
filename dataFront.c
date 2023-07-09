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

void pError(const char *errorStream, const char *errorText) {
    fprintf(stderr, "%s: %s\n", errorStream, errorText);
    exit(1);
}

void validateArguments(int argc, char *argv[]) {
    if (!validArgumentCount(argc)) {
        pError("main", "invalid argument count.");
    }
}

void createFiles(FILE **files, char *argv[], int count, char *flag) {
    if (strcmp(flag, "r") != 0 && strcmp(flag, "w") != 0) {
        pError("file(s):", "Not a valid read/write flag.");
    }
    int valid = newFiles(files, argv, count, flag);
    if (!valid) {
        pError("file(s):", "Permission denied.");
    }
    if (strcmp(flag, "r") == 0)
        puts("Files have been loaded successfully.");
    if (strcmp(flag, "w") == 0)
        puts("Files have been created successfully.");
}

void loadDataToADT(bikeSharingADT bs, FILE **files, char *argv) {
    int valid = putDataToADT(bs, files, argv);

    if (!valid) {
        pError("main", "Failed to load data to ADT.");
    }

    puts("Data has been loaded correctly.");
}

void validateQuery(int status) {
    if (status < 0)
        pError("main", "Error while loading data to query.");
}
