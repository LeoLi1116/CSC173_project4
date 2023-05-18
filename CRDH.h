/*
 * CRDH.h
 *
 *  Created on: 2021Äê11ÔÂ15ÈÕ
 *      Author: 13410
 */

#ifndef CRDH_H_
#define CRDH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CRDH* CRDH;

extern CRDH new_CRDH(char* class, char* room, char* day, char* hour);

extern void set_CRDH(CRDH this, char* class,  char* room, char* day, char* hour);

extern void set_CRDH_course(CRDH a, char* class);

extern void set_CRDH_day(CRDH a, char* day);

extern void set_CRDH_hour(CRDH a, char* hour);

extern void set_CRDH_room (CRDH a, char* room);

extern void set_pCRDH_null(CRDH a);

extern void set_nCRDH_null(CRDH a);

extern void remove_this_CRDH(CRDH prev, CRDH cur);

extern char* get_CRDH_class(CRDH a);

extern char* get_CRDH_day(CRDH a);

extern char* get_CRDH_hour(CRDH a);

extern char* get_CRDH_room(CRDH a);

extern CRDH get_CRDH_next(CRDH a);

extern CRDH get_CRDH_prev(CRDH a);

extern int have_CRDH_next(CRDH a);

extern int have_CRDH_prev(CRDH a);

extern void insert_CRDH_next(CRDH this, CRDH* next);

extern void remove_CRDH_next(CRDH this);

extern int matchCRDH(CRDH a, CRDH b);

extern void freeCRDH(CRDH a);

#endif /* CRDH_H_ */
