


#ifndef CSG_H_
#define CSG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct CSG* CSG;


extern CSG new_CSG(char* course, int sid, char* grade);

extern void set_CSG(CSG this, char* course, int sid, char* grade);

extern void set_course(CSG a, char* course);

extern void set_grade(CSG a, char* grade);

extern void set_sid(CSG a, int sid);

extern void set_prev_null(CSG a);

extern void set_next_null(CSG a);

extern void remove_this_CSG(CSG prev, CSG cur);

extern char* get_course(CSG a);

extern char* get_grade(CSG a);

extern int get_sid (CSG a);

extern CSG get_next(CSG a);

extern CSG get_prev(CSG a);

extern int have_next(CSG a);

extern int have_prev(CSG a);

extern void insert_next(CSG this, CSG* next);

extern void remove_next(CSG this);

extern int matchCSG(CSG a, CSG b);

extern void freeCSG(CSG a);

#endif /* CSG_H_ */
