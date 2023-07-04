#include "dataFront.h"
#include "dataProcessing.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME 0
#define FILES_COUNT 2

void pError(const char* errorStream, const char* errorText)
{
    fprintf(stderr, "%s: %s.\n", errorStream, errorText);
    exit(1);
}

void validateArguments(int argc, char* argv[]) {
    if (!validArgumentCount(argc)) {
        pError("main", "invalid argument count.");
    }
}

void loadDataToADT(bikeSharingADT bs, FILE* files[FILES_COUNT], char* argv) {
    int valid = putDataToADT(bs, files, argv);

    if (!valid) {
        pError("main", "Failed to load data to ADT.");
    }

    printf("Success.\n");
}
