/******************************************************************************
 *
 * @file    bikeSharingADT.h
 *
 * @brief   ADT para manejo de datos y queries.
 *
 * @author  Lucas Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipe Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 * @date    5/07/2023
 *
 ******************************************************************************/

#ifndef __bikesharingadt_h_
#define __bikesharingadt_h_

#include <stdio.h>
typedef struct bikeSharingCDT *bikeSharingADT;

/******************************************************************************
 *
 * @category    CONSTRUCTOR FUNCTION
 *
 ******************************************************************************/
bikeSharingADT newBikeSharingADT(void);

/******************************************************************************
 *
 * @category    FUNCTIONS
 *
 ******************************************************************************/
int addStation(bikeSharingADT bs, char *stationName, size_t id);
int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char isMember);


/******************************************************************************
 *
 * @category    GETTER FUNCTIONS
 *
 ******************************************************************************/
size_t getTotalMemberRents(bikeSharingADT bs, size_t id);
char * getStationName(bikeSharingADT bs, size_t id);
size_t getSize(bikeSharingADT bs);

/******************************************************************************
 *
 * @category    FREE MEMORY
 *
 * @brief       Libera todos los recursos utilizados por el ADT.
 *
 ******************************************************************************/
void freeBikeSharing(bikeSharingADT bs);

/******************************************************************************
 *
 * @category    SORTING FUNCTIONS
 *
 ******************************************************************************/

//  Sortea por Qty of Rents (miembros) de forma descendente.
void sortStationsByRent(bikeSharingADT bs);

// Sortea por ID, en forma ascendente.
void sortStationsById(bikeSharingADT bs);

// Sortea por nombre de estacion en forma alfabetica.
void sortStationsByAlpha(bikeSharingADT bs);

void getRentsByMonth(bikeSharingADT bs, size_t stationIndex, int* monthArray);

size_t getTotalRentsBetweenStations(bikeSharingADT bs, size_t startIndex, size_t endIndex);

#endif
