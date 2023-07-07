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

/*
 * @brief Constructor del ADT.
 */
bikeSharingADT newBikeSharingADT(void);

/*
 * FUNCIONES EXTRAS
 */
int addStation(bikeSharingADT bs, char *stationName, size_t id);
int addRent(bikeSharingADT bs, int startMonth, size_t startId, size_t endId, char isMember);



size_t getId(bikeSharingADT bs, size_t id);
size_t getStationCount(bikeSharingADT bs);
int getType(bikeSharingADT bs);
size_t getTotalRents(bikeSharingADT bs, size_t id);
size_t getTotalMemberRents(bikeSharingADT bs, size_t id);
char * getStationName(bikeSharingADT bs, size_t id);
size_t getSize(bikeSharingADT bs);
char isUsed(bikeSharingADT bs, size_t id);

void setType(bikeSharingADT bs, int type);

/*
 * @brief Libera todos los recursos utilizados por el ADT.
 */
void freeBikeSharing(bikeSharingADT bs);

void printEndRentsArray(bikeSharingADT bs, size_t index);
void printName(bikeSharingADT bs, size_t id);
void printList(bikeSharingADT bs);
void printTotalRents(bikeSharingADT bs, size_t id);
void sortStationsByRent(bikeSharingADT bs);
void sortStationsById(bikeSharingADT bs);
void sortStationsByAlpha(bikeSharingADT bs);

size_t getTotalRentsBetweenStations(bikeSharingADT bs, size_t startIndex, size_t endIndex);

#endif
