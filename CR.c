/*
 * CR.c
 *
 *  Created on: 2021Äê11ÔÂ14ÈÕ
 *      Author: 13410
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CR.h"


struct CR {
	char* class;
	char* room;
	CR* prev;
	CR* next;
};


CR new_CR(char* class,  char* room){
	CR this = (CR) malloc(sizeof(struct CR));
	set_CR(this, class, room);
	this->prev = NULL;
	this->next = NULL;
	return this;
}

void set_CR(CR this, char* class,  char* room){
	set_CR_class(this, class);
	set_room(this, room);
}

void set_CR_class(CR a, char* class){
	a -> class = class;
}

void set_room(CR a, char* room){
	a-> room = room;
}

void set_pCR_null(CR a){
	a-> prev = NULL;
}

void set_nCR_null(CR a){
	a->next = NULL;
}

void remove_this_CR(CR prev, CR cur){
	prev-> next = cur -> next;
}

char* get_CR_class(CR a){
	return a-> class;
}

char* get_room(CR a){
	return a-> room;
}

CR get_CR_next(CR a){
	return *(a-> next);
}

CR get_CR_prev(CR a){
	return *(a->prev);
}

int have_CR_next(CR a){
	if (a->next == NULL){
		return 0;
	}
	return 1;

}

int have_CR_prev(CR a){
	if (a->prev == NULL){
		return 0;
	}
	return 1;
}

void insert_CR_next(CR this, CR* next){
	if (have_CR_next(this)== 0){
		this-> next = (CR*) malloc(sizeof(CR*));
		*this->next = *next;
		CR last = *next;
		last->prev = (CR*) malloc(sizeof(CR*));
		*last->prev = this;

		}
	else{
		insert_CR_next(get_CR_next(this), next);
	}
}

void remove_CR_next(CR this){
	this->next = NULL;
}

int matchCR(CR a, CR b){
	if (strcmp(get_CR_class(a),get_CR_class(b))==0 && strcmp(get_room(a),get_room(b))==0){
			return 1;
		}
		return 0;
}

void freeCR(CR a){
	a->prev = NULL;
	a->next = NULL;
	free(a-> prev);
	free(a-> next);
	free(a);
}
