/******************************************************************************
 *
 * @file    bikeSharingADT.h
 *
 * @brief   ADT para manejo de datos y queries.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
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



void setType(bikeSharingADT bs, int type);

/*
 * @brief Libera todos los recursos utilizados por el ADT.
 */
void freeBikeSharing(bikeSharingADT bs);

void printName(bikeSharingADT bs, size_t id);

#endif
