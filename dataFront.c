#include "dataFront.h"
#include "dataProcessing.h"
#include <stdio.h>
#include <stdlib.h>

void pError(const char* errorStream, const char* errorText)
{
    fprintf(stderr, "%s: %s.\n", errorStream, errorText);
    exit(1);
}

void validateArguments(int argc, char* argv[])
{
    if (!validArgumentCount(argc)) {
        pError("main", "invalid argument count.");
    }
//    if (!validArgumentFormat(argv[]))
}

//void validateFilesFormat(char buff[], int buffSize, FILE** bikeFile, FILE** stationFile, char* bikeFormat, char* stationFormat)
//{
//    if (!validFilesFormat(buff, buffSize, bikeFile, stationFile, bikeFormat, stationFormat)) {
//        pError("main", "files format invalid.");
//    }
//}
