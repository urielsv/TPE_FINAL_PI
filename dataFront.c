#include "dataFront.h"
#include "dataProcessing.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME 0
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
// validar el putDataToADT si tira error.
