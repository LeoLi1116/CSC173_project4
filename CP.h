/*
 * CP.h
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: 13410
 */

#ifndef CP_H_
#define CP_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct CP* CP;


extern CP new_CP(char* class,  char* pre);

extern void set_CP(CP this, char* class,  char* pre);

extern void set_class(CP a, char* class);

extern void set_pre(CP a, char* pre);

extern void set_pCP_null(CP a);

extern void set_nCP_null(CP a);

extern void remove_this_CP(CP prev, CP cur);

extern char* get_class(CP a);

extern char* get_pre(CP a);

extern CP get_CP_next(CP a);

extern CP get_CP_prev(CP a);

extern int have_CP_next(CP a);

extern int have_CP_prev(CP a);

extern void insert_CP_next(CP this, CP* next);

extern void remove_CP_next(CP this);

extern int matchCP(CP a, CP b);

extern void freeCP(CP a);


#endif /* CP_H_ */
