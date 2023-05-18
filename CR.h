/*
 * CR.h
 *
 *  Created on: 2021Äê11ÔÂ14ÈÕ
 *      Author: 13410
 */

#ifndef CR_H_
#define CR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct CR* CR;

extern CR new_CR(char* class,  char* room);

extern void set_CR(CR this, char* class,  char* room);

extern void set_CR_class(CR a, char* class);

extern void set_room(CR a, char* room);

extern void set_pCR_null(CR a);

extern void set_nCR_null(CR a);

extern void remove_this_CR(CR roomv, CR cur);

extern char* get_CR_class(CR a);

extern char* get_room(CR a);

extern CR get_CR_next(CR a);

extern CR get_CR_prev(CR a);

extern CR get_CR_room(CR a);

extern int have_CR_next(CR a);

extern int have_CR_prev(CR a);


extern int have_CR_room(CR a);

extern void insert_CR_next(CR this, CR* next);

extern void remove_CR_next(CR this);

extern int matchCR(CR a, CR b);

extern void freeCR(CR a);

#endif /* CR_H_ */
