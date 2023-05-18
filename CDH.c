#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDH.h"
#include "hashtable.h"

struct CDH {
	char* class;
	char* day;
	char* hour;
	CDH* prev;
	CDH* next;
};


CDH new_CDH(char* class,  char* day, char* hour){
	CDH this = (CDH) malloc(sizeof(struct CDH));
	    set_CDH(this, class, day, hour);
	    this->prev = NULL;
	    this->next = NULL;
	    return this;
}

void set_CDH(CDH this, char* class,  char* day, char* hour){
	set_CDH_class(this, class);
	set_day(this, day);
	set_hour(this,hour);
}

void set_CDH_class(CDH a, char* class){
	a -> class = class;
}

void set_day(CDH a, char* day){
	a-> day = day;
}

void set_hour(CDH a, char* hour){
	a-> hour = hour;
}


void set_pCDH_null(CDH a){
	a-> prev = NULL;
}

void set_nCDH_null(CDH a){
	a->next = NULL;
}

void remove_this_CDH(CDH prev, CDH cur){
	prev-> next = cur -> next;
}

char* get_CDH_class(CDH a){
	return a-> class;
}

char* get_day(CDH a){
	return a-> day;
}

char* get_hour(CDH a){
	return a-> hour;
}

CDH get_CDH_next(CDH a){
	return *(a-> next);
}

CDH get_CDH_prev(CDH a){
	return *(a->prev);
}

int have_CDH_next(CDH a){
	if (a->next == NULL){
		return 0;
	}
	return 1;

}

int have_CDH_prev(CDH a){
	if (a->prev == NULL){
		return 0;
	}
	return 1;
}

void insert_CDH_next(CDH this, CDH* next){
	if (have_CDH_next(this)== 0){
		this-> next = (CDH*) malloc(sizeof(CDH*));
		*this->next = *next;
		CDH last = *next;
		last->prev = (CDH*) malloc(sizeof(CDH*));
		*last->prev = this;

		}
	else{
		insert_CDH_next(get_CDH_next(this), next);
	}
}

void remove_CDH_next(CDH this){
	this->next = NULL;
}

int matchCDH(CDH a, CDH b){
	if (strcmp(get_CDH_class(a),get_CDH_class(b))==0 && strcmp(get_day(a),get_day(b))==0 && strcmp(get_hour(a),get_hour(b))==0){
			return 1;
		}
		return 0;
}


void freeCDH(CDH a){
	a->prev = NULL;
	a->next = NULL;
	free(a->prev);
	free(a->next);
	free(a);
}
