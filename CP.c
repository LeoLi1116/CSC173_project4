/*
 * CP.c
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: 13410
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CP.h"


struct CP {
	char* class;
	char* pre;
	CP* prev;
	CP* next;
};


CP new_CP(char* class,  char* pre){
	CP this = (CP) malloc(sizeof(struct CP));
	    set_CP(this, class, pre);
	    this->prev = NULL;
	    this->next = NULL;
	    return this;
}

void set_CP(CP this, char* class,  char* pre){
	set_class(this, class);
	set_pre(this, pre);
}

void set_class(CP a, char* class){
	a -> class = class;
}

void set_pre(CP a, char* pre){
	a-> pre = pre;
}

void set_pCP_null(CP a){
	a-> prev = NULL;
}

void set_nCP_null(CP a){
	a->next = NULL;
}

void remove_this_CP(CP prev, CP cur){
	prev-> next = cur -> next;
}

char* get_class(CP a){
	return a-> class;
}

char* get_pre(CP a){
	return a-> pre;
}

CP get_CP_next(CP a){
	return *(a-> next);
}

CP get_CP_prev(CP a){
	return *(a->prev);
}

int have_CP_next(CP a){
	if (a->next == NULL){
		return 0;
	}
	return 1;

}

int have_CP_prev(CP a){
	if (a->prev == NULL){
		return 0;
	}
	return 1;
}

void insert_CP_next(CP this, CP* next){
	if (have_CP_next(this)== 0){
		this-> next = (CP*) malloc(sizeof(CP*));
		*this->next = *next;
		CP last = *next;
		last->prev = (CP*) malloc(sizeof(CP*));
		*last->prev = this;

		}
	else{
		insert_CP_next(get_CP_next(this), next);
	}
}

void remove_CP_next(CP this){
	this->next = NULL;
}

int matchCP(CP a, CP b){
	if (strcmp(get_class(a),get_class(b))==0 && strcmp(get_pre(a),get_pre(b))==0){
			return 1;
		}
		return 0;
}

void freeCP(CP a){
	a->prev = NULL;
	a->next = NULL;
	free(a->prev);
	free(a->next);
	free(a);
}
