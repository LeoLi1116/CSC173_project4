/*
 * SNAP.c
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: 13410
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SNAP.h"




struct SNAP {
	char* adress;
	int sid;
	char* name;
	int phone;
	SNAP* prev;
	SNAP* next;
};



SNAP new_SNAP(int sid, char* name,  char* adress, int phone) {
    SNAP this = (SNAP) malloc(sizeof(struct SNAP));
    set_SNAP(this,sid, name, adress, phone);
    this->prev = NULL;
    this->next = NULL;
    return this;
}


void set_SNAP(SNAP this, int sid, char* name,  char* adress, int phone){
	set_adress(this, adress);
	set_SNAP_sid(this, sid);
	set_name(this, name);
	set_phone(this, phone);

}

void set_adress(SNAP a, char* adress){
	a-> adress = adress;
}

void set_SNAP_sid(SNAP a, int sid){
	a->sid = sid;
}

void set_name(SNAP a, char* name){
	a->name = name;
}

void set_phone(SNAP a, int phone){
	a->phone = phone;
}

void set_pSNAP_null(SNAP a){
	a -> prev = NULL;
}

void set_nSNAP_null(SNAP a){
	a->next = NULL;
}

void remove_this_SNAP(SNAP prev, SNAP cur){
	prev->next = cur -> next;
}


char* get_adress(SNAP a){
	return a->adress;
}

int get_SNAP_sid (SNAP a){
	return a -> sid;
}

int get_phone(SNAP a){
	return a -> phone;
}

char* get_name(SNAP a){
	return a->name;
}

SNAP get_SNAP_next(SNAP a){
	return *(a-> next);
}

SNAP get_SNAP_prev(SNAP a){
	return *(a->prev);
}


int have_SNAP_prev(SNAP a){
	if (a->prev == NULL){
			return 0;
		}
		return 1;
}

int have_SNAP_next(SNAP a){
	if (a->next == NULL){
		return 0;
	}
	return 1;
}

void insert_SNAP_next(SNAP this, SNAP* next){
	if (have_SNAP_next(this)== 0){
		this-> next = (SNAP*) malloc(sizeof(SNAP*));
		*this->next = *next;
		SNAP last = *next;
		last->prev = (SNAP*) malloc(sizeof(SNAP*));
		*last->prev = this;

	}
	else{
		insert_SNAP_next(get_SNAP_next(this), next);
	}
}


void remove_SNAP_next(SNAP this){
	this->next = NULL;
}


int matchSNAP(SNAP a, SNAP b){

	if (get_SNAP_sid(a) == get_SNAP_sid(b) && strcmp(get_name(a),get_name(b))==0 && strcmp(get_adress(a),get_adress(b))==0 && get_phone(a) == get_phone(b)){
		return 1;
	}
	return 0;
}

void freeSNAP(SNAP a){
	a->prev = NULL;
	a->next = NULL;
	free(a->prev);
	free(a->next);
	free(a);
}

