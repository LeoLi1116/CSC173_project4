
#ifndef CDH_H_
#define CDH_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CDH* CDH;


extern CDH new_CDH(char* class, char* day, char* hour);

extern void set_CDH(CDH this, char* class,  char* day, char* hour);

extern void set_CDH_class(CDH a, char* class);

extern void set_day(CDH a, char* day);

extern void set_hour(CDH a, char* hour);


extern void set_pCDH_null(CDH a);

extern void set_nCDH_null(CDH a);

extern void remove_this_CDH(CDH prev, CDH cur);

extern char* get_CDH_class(CDH a);

extern char* get_day(CDH a);

extern char* get_hour(CDH a);


extern CDH get_CDH_next(CDH a);

extern CDH get_CDH_prev(CDH a);

extern int have_CDH_next(CDH a);

extern int have_CDH_prev(CDH a);

extern void insert_CDH_next(CDH this, CDH* next);

extern void remove_CDH_next(CDH this);

extern int matchCDH(CDH a, CDH b);

extern void freeCDH(CDH a);


#endif /* CDH_H_ */
