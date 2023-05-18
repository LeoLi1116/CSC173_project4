/*
 * SNAP.h
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: 13410
 */

#ifndef SNAP_H_
#define SNAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct SNAP* SNAP;


extern SNAP new_SNAP(int sid, char* name,  char* adress, int phone);

extern void set_SNAP(SNAP this, int sid, char* name,  char* adress, int phone);

extern void set_SNAP_sid(SNAP a, int sid);

extern void set_name(SNAP a, char* name);

extern void set_adress(SNAP a, char* adress);

extern void set_phone(SNAP a, int phone);

extern void set_pSNAP_null(SNAP a);

extern void set_nSNAP_null(SNAP a);

extern void remove_this_SNAP(SNAP prev, SNAP cur);

extern char* get_name(SNAP a);

extern char* get_adress(SNAP a);

extern int get_SNAP_sid (SNAP a);

extern int get_phone (SNAP a);

extern SNAP get_SNAP_next(SNAP a);

extern SNAP get_SNAP_prev(SNAP a);

extern int have_SNAP_next(SNAP a);

extern int have_SNAP_prev(SNAP a);

extern void insert_SNAP_next(SNAP this, SNAP* next);

extern void remove_SNAP_next(SNAP this);

extern int matchSNAP(SNAP a, SNAP b);

extern void freeSNAP(SNAP a);

#endif /* SNAP_H_ */
