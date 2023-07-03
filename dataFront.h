#ifndef __datafront_h_
#define __datafront_h_

void pError(const char* errorStream, const char* errorText);
void validateArguments(int argc, char* argv[]);
void validateFilesFormat(char buff[], int buffSize, FILE** bikeFile, FILE** stationFile, char* bikeFormat, char* stationFormat);

#endif