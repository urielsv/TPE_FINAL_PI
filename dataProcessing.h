#ifndef DATA_PROCESSING
#define DATA_PROCESSING
#include <stdio.h> // sus?

void validateArgumentCount(int argc);
void validateQueriesFormat(char buff[], int buffSize, FILE** bikeQuery, FILE** stationQuery,
                           char* bikeFormat, char* stationFormat);
void getArgumentFormat(char* argv, char* format[]);
#endif
