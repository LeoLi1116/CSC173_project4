#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRDH.h"
#include "hashtable.h"

struct CRDH {
	char* class;
	char* room;
	char* day;
	char* hour;
	CRDH* prev;
	CRDH* next;
};


CRDH new_CRDH(char* class, char* room, char* day, char* hour){
	CRDH this = (CRDH) malloc(sizeof(struct CRDH));
	    set_CRDH(this, class, room, day, hour);
	    this->prev = NULL;
	    this->next = NULL;
	    return this;
}

void set_CRDH(CRDH this, char* class, char*room, char* day, char* hour){

	this -> class = class;
	this -> room = room;
	this -> day= day;
	this -> hour = hour;

}


void set_pCRDH_null(CRDH a){
	a-> prev = NULL;
}

void set_nCRDH_null(CRDH a){
	a-> next = NULL;
}

void remove_this_CRDH(CRDH prev, CRDH cur){
	prev-> next = cur -> next;
}

char* get_CRDH_class(CRDH a){
	return a-> class;
}

char* get_CRDH_day(CRDH a){
	return a-> day;
}

char* get_CRDH_hour(CRDH a){
	return a-> hour;
}

char* get_CRDH_room(CRDH a){
	return a-> room;
}

CRDH get_CRDH_next(CRDH a){
	return *(a-> next);
}

CRDH get_CRDH_prev(CRDH a){
	return *(a->prev);
}

int have_CRDH_next(CRDH a){
	if (a->next == NULL){
		return 0;
	}
	return 1;

}

int have_CRDH_prev(CRDH a){
	if (a->prev == NULL){
		return 0;
	}
	return 1;
}

void insert_CRDH_next(CRDH this, CRDH* next){
	if (have_CRDH_next(this)== 0){
		this-> next = (CRDH*) malloc(sizeof(CRDH*));
		*this->next = *next;
		CRDH last = *next;
		last->prev = (CRDH*) malloc(sizeof(CRDH*));
		*last->prev = this;

		}
	else{
		insert_CRDH_next(get_CRDH_next(this), next);
	}
}

void remove_CRDH_next(CRDH this){
	this->next = NULL;
}

int matchCRDH(CRDH a, CRDH b){
	if (strcmp(get_CRDH_class(a),get_CRDH_class(b))==0 && strcmp(get_CRDH_day(a),get_CRDH_day(b))==0 && strcmp(get_CRDH_hour(a),get_CRDH_hour(b))==0 && strcmp(get_CRDH_room(a),get_CRDH_room(b))==0){
			return 1;
		}
		return 0;
}

void freeCRDH(CRDH a){
	a->prev = NULL;
	a->next = NULL;
	free(a->prev);
	free(a->next);
	free(a);
}

