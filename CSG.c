#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSG.h"




struct CSG {
	char* course;
	int sid;
	char* grade;
	CSG* prev;
	CSG* next;
};



CSG new_CSG(char* course, int sid, char* grade) {
    CSG this = (CSG) malloc(sizeof(struct CSG));
    set_CSG(this,course,sid,grade);
    this->prev = NULL;
    this->next = NULL;
    return this;
}


void set_CSG(CSG this, char* course, int sid, char* grade){
	set_course(this, course);
	set_sid(this, sid);
	set_grade(this, grade);

}

void set_course(CSG a, char* course){
	a-> course = course;
}

void set_sid(CSG a, int sid){
	a->sid = sid;
}

void set_grade(CSG a, char* grade){
	a->grade = grade;
}

void set_prev_null(CSG a){
	a -> prev = NULL;
}

void set_next_null(CSG a){
	a->next = NULL;
}

void remove_this_CSG(CSG prev, CSG cur){
	prev->next = cur -> next;
}


char* get_course(CSG a){
	return a->course;
}

int get_sid (CSG a){
	return a -> sid;
}

char* get_grade(CSG a){
	return a->grade;
}

CSG get_next(CSG a){
	return *(a-> next);
}

CSG get_prev(CSG a){
	return *(a->prev);
}


int have_prev(CSG a){
	if (a->prev == NULL){
			return 0;
		}
		return 1;
}

int have_next(CSG a){
	if (a->next == NULL){
		return 0;
	}
	return 1;
}

void insert_next(CSG this, CSG* next){
	if (have_next(this)== 0){
		this-> next = (CSG*) malloc(sizeof(CSG*));
		*this->next = *next;
		CSG last = *next;
		last->prev = (CSG*) malloc(sizeof(CSG*));
		*last->prev = this;

	}
	else{
		insert_next(get_next(this), next);
	}
}


void remove_next(CSG this){
	this->next = NULL;
}


int matchCSG(CSG a, CSG b){

	if (get_sid(a) == get_sid(b) && strcmp(get_course(a),get_course(b))==0 && strcmp(get_grade(a),get_grade(b))==0){
		return 1;
	}
	return 0;
}

void freeCSG(CSG a){
	a->prev = NULL;
	a->next = NULL;
	free(a->prev);
	free(a->next);
	free(a);
}



