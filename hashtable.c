/*
 * hashtable.c
 *
 *  Created on: 2021Äê11ÔÂ10ÈÕ
 *      Author: 13410
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSG.h"
#include "SNAP.h"
#include "CP.h"
#include "CDH.h"
#include "CR.h"
#include "CRDH.h"
#include "LinkedList.h"
#include "hashtable.h"



typedef struct hashtable *hashtable;

struct hashtable {
	void* list[10];
};

hashtable new_hashtable(){
	hashtable this = (hashtable) malloc(sizeof(struct hashtable));
	for(int i = 0; i <10; i++){
		this->list[i] = NULL;
	}
	return this;
}

void set_first(hashtable table, int key, void* data){
	table ->list[key] = data;
}

//CSG
void remove_CSG(hashtable table, CSG this){

	if(have_prev(this) && have_next(this)){
		CSG prev = get_prev(this);
		remove_this_CSG(prev, this);
	}
	else if (have_prev (this) == 0 && have_next(this)){
		int key = get_sid(this) % 10;
		CSG next = get_next(this);
		set_prev_null(next);
		set_first(table, key, next);

	}
	else if (have_prev(this) && have_next(this) == 0){
		CSG prev = get_prev(this);
		set_next_null(prev);

	}
	else{
		int key = get_sid(this) % 10;
		set_first(table, key, NULL);
	}
	set_prev_null(this);
}

void insertCSG (hashtable table, CSG a){

	if(CSGintable (table, a) == 0){

		int key = get_sid(a) % 10;

		if(table-> list[key] == NULL){
			table->list[key] = a;
		}
		else{
			CSG* ap = &a;
			insert_next((CSG) table->list[key], ap);
		}

	}
	return;
}

int CSGintable (hashtable table, CSG a){
	int key = get_sid(a) % 10;

	if(table->list[key] != NULL){
		CSG cur = (CSG) table->list[key];


		while (cur != NULL){
			if (matchCSG(cur, a)) {
				return 1;
			}

			if(have_next(cur)){
				cur = get_next(cur);
			}
			else{
				break;
			}
		}


	}
	return 0;
}

void deleteCSG(hashtable table, char* course, int sid, char* grade){
	if (sid != -1){
			int key = sid % 10;
			if(table->list[key]==NULL){
				return;
			}
			else{
				CSG cur = (CSG) table->list[key];
				while(cur != NULL){
					CSG next = NULL;
					if(strcmp (course, "*") == 0 && strcmp(grade, "*")==0){
						if (get_sid(cur) == sid){
							remove_CSG(table,cur);

							if(have_next(cur)){
								next = get_next(cur);
							}

						}
					}
					else if(strcmp(course, "*") == 0 && strcmp (grade, "*") != 0){
						if (get_sid(cur) == sid && strcmp(grade, get_grade(cur)) == 0){
							remove_CSG(table,cur);
							if(have_next(cur)){
								next = get_next(cur);
							}
						}
					}
					else if(strcmp(course, "*")!= 0 && strcmp(grade,"*") == 0){
						if (get_sid(cur) == sid && strcmp(course, get_course(cur)) == 0){
							remove_CSG(table,cur);

							if(have_next(cur)){
								next = get_next(cur);
							}

						}
					}
					else{
						if (get_sid(cur) == sid && strcmp(grade, get_grade(cur)) == 0 && strcmp(course, get_course(cur)) == 0){
							remove_CSG(table,cur);
							if(have_next(cur)){
								set_next_null(cur);
							}
							break;
						}
					}


					if(next != NULL){
						next = get_next(cur);
						remove_next(cur);
						cur = next;
					}
					else if (have_next(cur)){
						cur = get_next(cur);

					}
					else{
						break;
					}

				}
			}
	}
	else {
		for(int i = 0; i < 10; i++){
			CSG cur;
			if(table->list[i] == NULL){
				cur = NULL;
			}
			else{
				cur = (CSG) table->list[i];
			}
			while(cur != NULL){
				CSG next = NULL;
				if(strcmp (course, "*") == 0 && strcmp(grade, "*")==0){
					i = 10;
					break;
				}
				else if(strcmp (course, "*") != 0 && strcmp(grade, "*")==0){

					if (strcmp(course, get_course(cur)) == 0){
						remove_CSG(table,cur);
						if(have_next(cur)){
							next = get_next(cur);
						}
					}

				}
				else if (strcmp (course, "*") == 0 && strcmp(grade, "*")!=0){
					if (strcmp(grade, get_grade(cur)) == 0){
						remove_CSG(table,cur);
						if(have_next(cur)){
							next = get_next(cur);
						}
					}
				}
				else {
					if (strcmp(course, get_course(cur)) == 0 && strcmp(grade, get_grade(cur)) == 0){
						remove_CSG(table,cur);
						if(have_next(cur)){
							next = get_next(cur);
						}
					}
				}

				if(next != NULL){
					CSG next = get_next(cur);
					remove_next(cur);
					cur = next;
				}
				else if (have_next(cur)){
					cur = get_next(cur);
				}
				else{
					break;
				}
			}

		}
	}

}

LinkedList lookupCSG(hashtable table, char* course, int sid, char* grade){
	LinkedList ans = new_LinkedList();
	if (sid != -1){
		int key = sid % 10;

		if (table->list[key] == NULL){
			return ans;;
		}
		else{
			CSG cur = (CSG) table->list[key];

			while(cur != NULL){
				if(strcmp (course, "*") == 0 && strcmp(grade, "*")==0){
					if (get_sid(cur) == sid){
						LinkedList_add_at_end(ans, cur);
					}
				}
				else if(strcmp(course, "*") == 0 && strcmp (grade, "*") != 0){
					if (get_sid(cur) == sid && strcmp(grade, get_grade(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
					}
				}
				else if(strcmp(course, "*")!= 0 && strcmp(grade,"*") == 0){
					if (get_sid(cur) == sid && strcmp(course, get_course(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
					}
				}
				else{
					if (get_sid(cur) == sid && strcmp(grade, get_grade(cur)) == 0 && strcmp(course, get_course(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
						break;
					}
				}

				if(have_next(cur)){
					cur = get_next(cur);
				}
				else{
					break;
				}


			}

		}
	}
	else{
		for(int i = 0; i < 10; i++){
			CSG cur;
			if(table->list[i] == NULL){
				cur = NULL;
			}
			else{
				cur = (CSG) table->list[i];
			}
			while(cur != NULL){

				if(strcmp (course, "*") == 0 && strcmp(grade, "*")==0){
					LinkedList_add_at_end(ans, cur);
						}
				else if(strcmp (course, "*") != 0 && strcmp(grade, "*")==0){

					if (strcmp(course, get_course(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
					}

				}
				else if (strcmp (course, "*") == 0 && strcmp(grade, "*")!=0){
					if (strcmp(grade, get_grade(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
					}
				}
				else {
					if (strcmp(course, get_course(cur)) == 0 && strcmp(grade, get_grade(cur)) == 0){
						LinkedList_add_at_end(ans, cur);
					}
				}

				if(have_next(cur)){
					cur = get_next(cur);
				}
				else{
					break;
				}
			}

		}

	}
	return ans;
}

//SNAP
void remove_SNAP(hashtable table, SNAP this){
	if(have_SNAP_prev(this) && have_SNAP_next(this)){
			SNAP prev = get_SNAP_prev(this);
			remove_this_SNAP(prev, this);
		}
		else if (have_SNAP_prev (this) == 0 && have_SNAP_next(this)){
			int key = get_SNAP_sid(this) % 10;
			SNAP next = get_SNAP_next(this);
			set_pSNAP_null(next);
			set_first(table, key, next);

		}
		else if (have_SNAP_prev(this) && have_SNAP_next(this) == 0){
			SNAP prev = get_SNAP_prev(this);
			set_nSNAP_null(prev);

		}
		else{
			int key = get_SNAP_sid(this) % 10;
			set_first(table, key, NULL);
		}
		set_pSNAP_null(this);
}

void insertSNAP(hashtable table, SNAP a ){
	if(SNAPintable (table, a) == 0){

			int key = get_SNAP_sid(a) % 10;

			if(table-> list[key] == NULL){
				table->list[key] = a;
			}
			else{
				SNAP* ap = &a;
				insert_SNAP_next((SNAP) table->list[key], ap);
			}

		}
		return;
}

int SNAPintable(hashtable table, SNAP a){
	int key = get_SNAP_sid(a) % 10;

		if(table->list[key] != NULL){
			SNAP cur = (SNAP) table->list[key];


			while (cur != NULL){
				if (matchSNAP(cur, a)) {
					return 1;
				}

				if(have_SNAP_next(cur)){
					cur = get_SNAP_next(cur);
				}
				else{
					break;
				}
			}

		}
		return 0;
}

void deleteSNAP(hashtable table, int sid, char* name, char* adress, int phone){
	if (sid != -1){
			int key = sid % 10;
			if(table->list[key]==NULL){
				return;
			}
			else{
				SNAP cur = (SNAP) table->list[key];
				while(cur != NULL){
					SNAP next = NULL;
					if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone == -1){
						if (get_SNAP_sid(cur) == sid){
							remove_SNAP(table,cur);

							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else if(strcmp(name, "*") == 0 && strcmp (adress, "*") != 0 && phone == -1){
						if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0){
							remove_SNAP(table,cur);
							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}
						}
					}
					else if(strcmp(name, "*")!= 0 && strcmp(adress,"*") == 0 && phone == -1){
						if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0){
							remove_SNAP(table,cur);

							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone != -1){
						if (get_SNAP_sid(cur) == sid && get_phone (cur) == phone){
							remove_SNAP(table,cur);


							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else if(strcmp (name, "*") != 0 && strcmp(adress, "*")==0 && phone != -1){
						if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0 && get_phone (cur) == phone){
							remove_SNAP(table,cur);

							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else if(strcmp (name, "*") == 0 && strcmp(adress, "*")!=0 && phone != -1){
						if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0 && get_phone (cur) == phone){
							remove_SNAP(table,cur);

							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else if(strcmp (name, "*") != 0 && strcmp(adress, "*")==0 && phone != -1){
						if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0 && get_phone (cur) == phone){
							remove_SNAP(table,cur);

							if(have_SNAP_next(cur)){
								next = get_SNAP_next(cur);
							}

						}
					}
					else{
						if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0 && strcmp(name, get_name(cur)) == 0 && phone == get_phone(cur)){
							remove_SNAP(table,cur);
							if(have_SNAP_next(cur)){
								set_nSNAP_null(cur);
							}
							break;
						}
					}


					if(next != NULL){
						SNAP next = get_SNAP_next(cur);
						remove_SNAP_next(cur);
						cur = next;
					}
					else if (have_SNAP_next(cur)){
						cur = get_SNAP_next(cur);
					}
					else{
						break;
					}

				}
			}
	}
	else {
		for(int i = 0; i < 10; i++){
			SNAP cur;
			if(table->list[i] == NULL){
				cur = NULL;
			}
			else{
				cur = (SNAP) table->list[i];
			}
			while(cur != NULL){
				SNAP next = NULL;
				if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone == -1){
					i = 10;
					printf("please enter at least one filter\n");
					break;
				}
				else if(strcmp (name, "*") != 0 && strcmp(adress, "*") == 0 && phone == -1){

					if (strcmp(name, get_name(cur)) == 0){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}
				else if(strcmp (name, "*") == 0 && strcmp(adress, "*") != 0 && phone == -1){

					if (strcmp(adress, get_adress(cur)) == 0){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}
				else if(strcmp (name, "*") == 0 && strcmp(adress, "*") == 0 && phone != -1){
					if (phone == get_phone(cur)){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}
				else if(strcmp (name, "*") != 0 && strcmp(adress, "*") != 0 && phone == -1){
					if (strcmp(name, get_name(cur)) == 0 && strcmp(adress, get_adress(cur)) == 0 ){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}
				else if(strcmp (name, "*") != 0 && strcmp(adress, "*") == 0 && phone != -1){
					if (strcmp(name, get_name(cur)) == 0 && phone == get_phone(cur)){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}
				else if(strcmp (name, "*") == 0 && strcmp(adress, "*") != 0 && phone != -1){
					if (strcmp(adress, get_adress(cur)) == 0 && phone == get_phone(cur)){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}

				else {
					if (strcmp(name, get_name(cur)) == 0 && strcmp(adress, get_adress(cur)) == 0 && phone == get_phone(cur)){
						remove_SNAP(table,cur);
						if(have_SNAP_next(cur)){
							next = get_SNAP_next(cur);
						}
					}
				}

				if(next != NULL){
					SNAP next = get_SNAP_next(cur);
					remove_SNAP_next(cur);
					cur = next;
				}
				else if (have_SNAP_next(cur)){
					cur = get_SNAP_next(cur);
				}
				else{
					break;
				}
			}

		}
	}
}

LinkedList lookupSNAP(hashtable table, int sid, char* name, char* adress, int phone){
	LinkedList ans = new_LinkedList();

	if (sid != -1){
				int key = sid % 10;
				if(table->list[key]==NULL){
					return ans;
				}
				else{
					SNAP cur = (SNAP) table->list[key];
					while(cur != NULL){
						if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone == -1){
							if (get_SNAP_sid(cur) == sid){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp(name, "*") == 0 && strcmp (adress, "*") != 0 && phone == -1){
							if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp(name, "*")!= 0 && strcmp(adress,"*") == 0 && phone == -1){
							if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone != -1){
							if (get_SNAP_sid(cur) == sid && get_phone (cur) == phone){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp (name, "*") != 0 && strcmp(adress, "*")==0 && phone != -1){
							if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0 && get_phone (cur) == phone){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp (name, "*") == 0 && strcmp(adress, "*")!=0 && phone != -1){
							if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0 && get_phone (cur) == phone){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else if(strcmp (name, "*") != 0 && strcmp(adress, "*")==0 && phone != -1){
							if (get_SNAP_sid(cur) == sid && strcmp(name, get_name(cur)) == 0 && get_phone (cur) == phone){
								LinkedList_add_at_end(ans, cur);

							}
						}
						else{
							if (get_SNAP_sid(cur) == sid && strcmp(adress, get_adress(cur)) == 0 && strcmp(name, get_name(cur)) == 0 && phone == get_phone(cur)){
								LinkedList_add_at_end(ans, cur);
								break;
							}
						}


						if(have_SNAP_next(cur)){
							cur = get_SNAP_next(cur);
						}
						else{
							break;
						}

					}
				}
		}
		else {
			for(int i = 0; i < 10; i++){
				SNAP cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (SNAP) table->list[i];
				}
				while(cur != NULL){
					if(strcmp (name, "*") == 0 && strcmp(adress, "*")==0 && phone == -1){
						LinkedList_add_at_end(ans, cur);
					}
					else if(strcmp (name, "*") != 0 && strcmp(adress, "*") == 0 && phone == -1){

						if (strcmp(name, get_name(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp (name, "*") == 0 && strcmp(adress, "*") != 0 && phone == -1){

						if (strcmp(adress, get_adress(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp (name, "*") == 0 && strcmp(adress, "*") == 0 && phone != -1){
						if (phone == get_phone(cur)){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp (name, "*") != 0 && strcmp(adress, "*") != 0 && phone == -1){
						if (strcmp(name, get_name(cur)) == 0 && strcmp(adress, get_adress(cur)) == 0 ){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp (name, "*") != 0 && strcmp(adress, "*") == 0 && phone != -1){
						if (strcmp(name, get_name(cur)) == 0 && phone == get_phone(cur)){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp (name, "*") == 0 && strcmp(adress, "*") != 0 && phone != -1){
						if (strcmp(adress, get_adress(cur)) == 0 && phone == get_phone(cur)){
							LinkedList_add_at_end(ans, cur);
						}
					}

					else {
						if (strcmp(name, get_name(cur)) == 0 && strcmp(adress, get_adress(cur)) == 0 && phone == get_phone(cur)){
							LinkedList_add_at_end(ans, cur);
						}
					}

					if(have_SNAP_next(cur)){
						cur = get_SNAP_next(cur);
					}
					else{
						break;
					}
				}

			}
		}
	return ans;
}

//CP
int CPkey(CP a){
	char* class = get_class(a);
	int k = 0;
	for (int i = 0; i < strlen(class); i++) {
		k += (int) class [i];
	    	}
	int key = k % 10;
	return key;
}

void remove_CP(hashtable table, CP this){
	if(have_CP_prev(this) && have_CP_next(this)){
			CP prev = get_CP_prev(this);
			remove_this_CP(prev, this);
		}
		else if (have_CP_prev (this) == 0 && have_CP_next(this)){
			int key = CPkey(this);
			CP next = get_CP_next(this);
			set_pCP_null(next);
			set_first(table, key, next);

		}
		else if (have_CP_prev(this) && have_CP_next(this) == 0){
			CP prev = get_CP_prev(this);
			set_nCP_null(prev);

		}
		else{
			int key = CPkey(this);
			set_first(table, key, NULL);
		}
		set_pCP_null(this);
}

void insertCP (hashtable table, CP a){

	if(CPintable (table, a) == 0){

		int key = CPkey(a);

		if(table-> list[key] == NULL){
			table->list[key] = a;
		}
		else{
			CP* ap = &a;
			insert_CP_next((CP) table->list[key], ap);
		}

	}
	return;
}

int CPintable (hashtable table, CP a){
	int key = CPkey(a);

	if(table->list[key] != NULL){
		CP cur = (CP) table->list[key];


		while (cur != NULL){
			if (matchCP(cur, a)) {
				return 1;
			}

			if(have_CP_next(cur)){
				cur = get_CP_next(cur);
			}
			else{
				break;
			}
		}

	}
	return 0;
}

void deleteCP(hashtable table, char* class, char* pre){
	if (strcmp(class, "*") != 0){
				CP forkey = new_CP(class, pre);
				int key = CPkey(forkey);
				if(table->list[key]==NULL){
					return;
				}
				else{
					CP cur = (CP) table->list[key];
					while(cur != NULL){
						CP next = NULL;
						if(strcmp(pre, "*")==0){
							if (strcmp(class,get_class(cur))==0){
								remove_CP(table,cur);

								if(have_CP_next(cur)){
									next = get_CP_next(cur);
								}

							}
						}
						else{
							if (strcmp(class, get_class(cur)) == 0 && strcmp(pre, get_pre(cur)) == 0){
								remove_CP(table,cur);
								if(have_CP_next(cur)){
									 set_nCP_null(cur);
								}
								break;
							}
						}


						if(next != NULL){
							CP next = get_CP_next(cur);
							remove_CP_next(cur);
							cur = next;
						}
						else if (have_CP_next(cur)){
							cur = get_CP_next(cur);
						}
						else{
							break;
						}

					}
				}
		}
		else {
			for(int i = 0; i < 10; i++){
				CP cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CP) table->list[i];
				}
				while(cur != NULL){
					CP next = NULL;
					if(strcmp(pre, "*")==0){
						i = 10;
						printf("please enter at least one filter\n");
						break;
					}
					else {
						if (strcmp(pre, get_pre(cur)) == 0){
							remove_CP(table,cur);
							if(have_CP_next(cur)){
								next = get_CP_next(cur);
							}
						}
					}

					if(next != NULL){
						CP next = get_CP_next(cur);
						remove_CP_next(cur);
						cur = next;
					}
					else if (have_CP_next(cur)){
						cur = get_CP_next(cur);
					}
					else{
						break;
					}
				}

			}
		}
}

LinkedList lookupCP(hashtable table, char* class, char* pre){
	LinkedList ans = new_LinkedList();
		if (strcmp(class,"*") != 0){

			CP forkey = new_CP(class, pre);
			int key = CPkey(forkey);

			if (table->list[key] == NULL){
				return ans;;
			}
			else{
				CP cur = (CP) table->list[key];

				while(cur != NULL){
					if(strcmp(pre, "*")==0){
						if (strcmp(class, get_class(cur))==0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else{
						if (strcmp(class, get_class(cur)) == 0 && strcmp(pre, get_pre(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
							break;
						}
					}

					if(have_CP_next(cur)){
						cur = get_CP_next(cur);
					}
					else{
						break;
					}


				}

			}
		}
		else{
			for(int i = 0; i < 10; i++){
				CP cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CP) table->list[i];
				}
				while(cur != NULL){

					if(strcmp(pre, "*")==0){
						LinkedList_add_at_end(ans, cur);
							}
					else {
						if (strcmp(pre, get_pre(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}

					if(have_CP_next(cur)){
						cur = get_CP_next(cur);
					}
					else{
						break;
					}
				}

			}

		}
		return ans;
}

//CDH
int CDHkey(CDH a){
	char* class = get_CDH_class(a);
	int k = 0;
	for (int i = 0; i < strlen(class); i++) {
		k += (int) class [i];
	}
	char* day = get_day(a);
	for (int i = 0; i < strlen(day); i++) {
		k += (int) day [i];
	}
	char* hour = get_hour(a);
	for (int i = 0; i < strlen(hour); i++) {
		k += (int) hour [i];
	}
	int key = k % 10;
	return key;
}

void remove_CDH(hashtable table, CDH this){
	if(have_CDH_prev(this) && have_CDH_next(this)){
		CDH prev = get_CDH_prev(this);
		remove_this_CDH(prev, this);
			}
	else if (have_CDH_prev (this) == 0 && have_CDH_next(this)){
		int key = CDHkey(this);
		CDH next = get_CDH_next(this);
		set_pCDH_null(next);
		set_first(table, key, next);

	}
	else if (have_CDH_prev(this) && have_CDH_next(this) == 0){
		CDH prev = get_CDH_prev(this);
		set_nCDH_null(prev);

	}
	else{
		int key = CDHkey(this);
		set_first(table, key, NULL);
	}
	set_pCDH_null(this);
}

void insertCDH(hashtable table, CDH a){
	if(CDHintable (table, a) == 0){

		int key = CDHkey(a);

		if(table-> list[key] == NULL){
			table->list[key] = a;
		}
		else{
			CDH* ap = &a;
			insert_CDH_next((CDH) table->list[key], ap);
		}

	}
	return;
}

int CDHintable (hashtable table, CDH a){
	int key = CDHkey(a);

	if(table->list[key] != NULL){
		CDH cur = (CDH) table->list[key];


		while (cur != NULL){
			if (matchCDH(cur, a)) {
				return 1;
			}

			if(have_CDH_next(cur)){
				cur = get_CDH_next(cur);
			}
			else{
				break;
			}
		}

	}
	return 0;
}

void deleteCDH(hashtable table, char* class, char* day, char* hour){
	if (strcmp(class, "*") != 0 && strcmp(day, "*") != 0 && strcmp(hour, "*") != 0){
				CDH forkey = new_CDH(class, day, hour);
				int key = CDHkey(forkey);
				if(table->list[key]==NULL){
					return;
				}
				else{
					CDH cur = (CDH) table->list[key];
					while (cur != NULL){
						if (strcmp(class, get_CDH_class(cur)) == 0 && strcmp(day, get_day(cur)) == 0 && strcmp(hour, get_hour(cur)) == 0){
							remove_CDH(table, cur);
						}
						if(have_CDH_next(cur)){
							set_nCDH_null(cur);
						}

						break;

					}

				}
		}
		else {
			for(int i = 0; i < 10; i++){
				CDH cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CDH) table->list[i];
				}
				while(cur != NULL){
					CDH next = NULL;
					if(strcmp(class, "*")==0 && strcmp(day, "*")==0 && strcmp(hour, "*")==0){
						i = 10;
						printf("please enter at least one filter\n");
						break;
					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")==0 && strcmp(hour, "*")==0){
						if (strcmp(class , get_CDH_class(cur)) == 0){
							remove_CDH(table,cur);

							if(have_CDH_next(cur)){
								next = get_CDH_next(cur);
							}
						}
					}
					else if(strcmp(class, "*")==0 && strcmp(day, "*")!=0 && strcmp(hour, "*")==0){
						if (strcmp(day , get_day(cur)) == 0){
							remove_CDH(table,cur);

							if(have_CDH_next(cur)){
								next = get_CDH_next(cur);
							}
						}
					}
					else if(strcmp(class, "*")==0 && strcmp(day, "*")==0 && strcmp(hour, "*")!=0){
						if (strcmp(hour , get_hour(cur)) == 0){
							remove_CDH(table,cur);

							if(have_CDH_next(cur)){
								next = get_CDH_next(cur);
							}
						}

					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")==0 && strcmp(hour, "*")!=0){
						if (strcmp(class , get_CDH_class(cur)) == 0 && strcmp(hour , get_hour(cur)) == 0){
							remove_CDH(table,cur);

							if(have_CDH_next(cur)){
								next = get_CDH_next(cur);
							}
						}
					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")!=0 && strcmp(hour, "*")==0){
						if (strcmp(class , get_CDH_class(cur)) == 0 && strcmp(hour , get_day(cur)) == 0){
							remove_CDH(table,cur);

							if(have_CDH_next(cur)){
								next = get_CDH_next(cur);
							}
						}
					}
					else{
						if (strcmp(hour , get_hour(cur)) == 0 && strcmp(day , get_day(cur)) == 0){
							remove_CDH(table,cur);
						}
						if(have_CDH_next(cur)){
							next = get_CDH_next(cur);
						}

					}

					if(next != NULL){
						next = get_CDH_next(cur);
						remove_CDH_next(cur);
						cur = next;
					}
					else if (have_CDH_next(cur)){
						cur = get_CDH_next(cur);
					}
					else{
						break;
					}
				}

			}
		}
}

LinkedList lookupCDH(hashtable table, char* class, char* day, char* hour){
	LinkedList ans = new_LinkedList();
	if (strcmp(class, "*") != 0 && strcmp(day, "*") != 0 && strcmp(hour, "*") != 0){
				CDH forkey = new_CDH(class, day, hour);
				int key = CDHkey(forkey);
				if(table->list[key]==NULL){
					return ans;
				}
				else{
					CDH cur = (CDH) table->list[key];
					while (cur != NULL){
						if (strcmp(class, get_CDH_class(cur)) == 0 && strcmp(day, get_day(cur)) == 0 && strcmp(hour, get_hour(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
							break;
						}
						else{
							if(have_CDH_next(cur)){
							cur = get_CDH_next(cur);
							}
							else{
								break;
							}
						}
					}

				}
		}
		else {
			for(int i = 0; i < 10; i++){
				CDH cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CDH) table->list[i];
				}
				while(cur != NULL){
					if(strcmp(class, "*")==0 && strcmp(day, "*")==0 && strcmp(hour, "*")==0){
						LinkedList_add_at_end(ans, cur);
					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")==0 && strcmp(hour, "*")==0){
						if (strcmp(class , get_CDH_class(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp(class, "*")==0 && strcmp(day, "*")!=0 && strcmp(hour, "*")==0){
						if (strcmp(day , get_day(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp(class, "*")==0 && strcmp(day, "*")==0 && strcmp(hour, "*")!=0){
						if (strcmp(hour , get_hour(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")==0 && strcmp(hour, "*")!=0){
						if (strcmp(class , get_CDH_class(cur)) == 0 && strcmp(hour , get_hour(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else if(strcmp(class, "*")!=0 && strcmp(day, "*")!=0 && strcmp(hour, "*")==0){
						if (strcmp(class , get_CDH_class(cur)) == 0 && strcmp(hour , get_day(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					else{
						if (strcmp(hour , get_hour(cur)) == 0 && strcmp(hour , get_day(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}
					if(have_CDH_next(cur)){
						cur = get_CDH_next(cur);
					}
					else{
						break;
					}
				}

			}
		}

	return ans;
}

//CR
int CRkey(CR a){
	char* class = get_CR_class(a);
	int k = 0;
	for (int i = 0; i < strlen(class); i++) {
		k += (int) class [i];
	    	}
	int key = k % 10;
	return key;
}

void remove_CR(hashtable table, CR this){
	if(have_CR_prev(this) && have_CR_next(this)){
			CR prev = get_CR_prev(this);
			remove_this_CR(prev, this);
		}
		else if (have_CR_prev (this) == 0 && have_CR_next(this)){
			int key = CRkey(this);
			CR next = get_CR_next(this);
			set_pCR_null(next);
			set_first(table, key, next);

		}
		else if (have_CR_prev(this) && have_CR_next(this) == 0){
			CR prev = get_CR_prev(this);
			set_nCR_null(prev);

		}
		else{
			int key = CRkey(this);
			set_first(table, key, NULL);
		}
		set_pCR_null(this);
}

void insertCR (hashtable table, CR a){

	if(CRintable (table, a) == 0){

		int key = CRkey(a);

		if(table-> list[key] == NULL){
			table->list[key] = a;
		}
		else{
			CR* ap = &a;
			insert_CR_next((CR) table->list[key], ap);
		}

	}
	return;
}

int CRintable (hashtable table, CR a){
	int key = CRkey(a);

	if(table->list[key] != NULL){
		CR cur = (CR) table->list[key];


		while (cur != NULL){
			if (matchCR(cur, a)) {
				return 1;
			}

			if(have_CR_next(cur)){
				cur = get_CR_next(cur);
			}
			else{
				break;
			}
		}

	}
	return 0;
}

void deleteCR(hashtable table, char* class, char* room){
	if (strcmp(class, "*") != 0){
				CR forkey = new_CR(class, room);
				int key = CRkey(forkey);
				if(table->list[key]==NULL){
					return;
				}
				else{
					CR cur = (CR) table->list[key];
					while(cur != NULL){
						CR next = NULL;
						if(strcmp(room, "*")==0){
							if (strcmp(class,get_CR_class(cur))==0){
								remove_CR(table,cur);

								if(have_CR_next(cur)){
									next = get_CR_next(cur);
								}

							}
						}
						else{
							if (strcmp(class, get_CR_class(cur)) == 0 && strcmp(room, get_room(cur)) == 0){
								remove_CR(table,cur);
								if(have_CR_next(cur)){
									 set_nCR_null(cur);
								}
								break;
							}
						}


						if(next != NULL){
							CR next = get_CR_next(cur);
							remove_CR_next(cur);
							cur = next;
						}
						else if (have_CR_next(cur)){
							cur = get_CR_next(cur);
						}
						else{
							break;
						}

					}
				}
		}
		else {
			for(int i = 0; i < 10; i++){
				CR cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CR) table->list[i];
				}
				while(cur != NULL){
					CR next = NULL;
					if(strcmp(room, "*")==0){
						i = 10;
						printf("please enter at least one filter\n");
						break;
					}
					else {
						if (strcmp(room, get_room(cur)) == 0){
							remove_CR(table,cur);
							if(have_CR_next(cur)){
								next = get_CR_next(cur);
							}
						}
					}

					if(next != NULL){
						CR next = get_CR_next(cur);
						remove_CR_next(cur);
						cur = next;
					}
					else if (have_CR_next(cur)){
						cur = get_CR_next(cur);
					}
					else{
						break;
					}
				}

			}
		}
}

LinkedList lookupCR(hashtable table, char* class, char* room){
	LinkedList ans = new_LinkedList();
		if (strcmp(class,"*") != 0){

			CR forkey = new_CR(class, room);
			int key = CRkey(forkey);

			if (table->list[key] == NULL){
				return ans;
			}
			else{
				CR cur = (CR) table->list[key];

				while(cur != NULL){
					if(strcmp(room, "*")==0){
						if (strcmp(class, get_CR_class(cur))==0){

							LinkedList_add_at_end(ans, cur);
						}
					}
					else{
						if (strcmp(class, get_CR_class(cur)) == 0 && strcmp(room, get_room(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
							break;
						}
					}

					if(have_CR_next(cur)){
						cur = get_CR_next(cur);
					}
					else{
						break;
					}


				}

			}
		}
		else{
			for(int i = 0; i < 10; i++){
				CR cur;
				if(table->list[i] == NULL){
					cur = NULL;
				}
				else{
					cur = (CR) table->list[i];
				}
				while(cur != NULL){

					if(strcmp(room, "*")==0){
						LinkedList_add_at_end(ans, cur);
							}
					else {
						if (strcmp(room, get_room(cur)) == 0){
							LinkedList_add_at_end(ans, cur);
						}
					}

					if(have_CR_next(cur)){
						cur = get_CR_next(cur);
					}
					else{
						break;
					}
				}

			}

		}
		return ans;
}


int CRDHkey(CRDH a){
	char* class = get_CRDH_class(a);
	int k = 0;
	for (int i = 0; i < strlen(class); i++) {
		k += (int) class [i];
	}
	char* day = get_CRDH_day(a);
	for (int i = 0; i < strlen(day); i++) {
		k += (int) day [i];
	}
	char* hour = get_CRDH_hour(a);
	for (int i = 0; i < strlen(hour); i++) {
		k += (int) hour [i];
	}
	int key = k % 10;
	return key;
}

void remove_CRDH(hashtable table, CRDH this){
	if(have_CRDH_prev(this) && have_CRDH_next(this)){
		CRDH prev = get_CRDH_prev(this);
		remove_this_CRDH(prev, this);
			}
	else if (have_CRDH_prev (this) == 0 && have_CRDH_next(this)){
		int key = CRDHkey(this);
		CRDH next = get_CRDH_next(this);
		set_pCRDH_null(next);
		set_first(table, key, next);

	}
	else if (have_CRDH_prev(this) && have_CRDH_next(this) == 0){
		CRDH prev = get_CRDH_prev(this);
		set_nCRDH_null(prev);

	}
	else{
		int key = CRDHkey(this);
		set_first(table, key, NULL);
	}
	set_pCRDH_null(this);
}

void insertCRDH(hashtable table, CRDH a){
	if(CRDHintable (table, a) == 0){

		int key = CRDHkey(a);

		if(table-> list[key] == NULL){
			table->list[key] = a;
		}
		else{
			CRDH* ap = &a;
			insert_CRDH_next((CRDH) table->list[key], ap);
		}

	}
	return;
}

int CRDHintable (hashtable table, CRDH a){
	int key = CRDHkey(a);

	if(table->list[key] != NULL){
		CRDH cur = (CRDH) table->list[key];


		while (cur != NULL){
			if (matchCRDH(cur, a)) {
				return 1;
			}

			if(have_CRDH_next(cur)){
				cur = get_CRDH_next(cur);
			}
			else{
				break;
			}
		}

	}
	return 0;
}

LinkedList lookupCRDH(hashtable table, char* room){
	LinkedList ans = new_LinkedList();

	for(int i = 0; i < 10; i++){
		CRDH cur;
		if(table->list[i] == NULL){
			cur = NULL;
		}
		else{
			cur = (CRDH) table->list[i];

			while(cur != NULL){

				if(strcmp(room, get_CRDH_room(cur))==0){
					LinkedList_add_at_end(ans, cur);
				}
				else if(strcmp(room,"*")==0){
					LinkedList_add_at_end(ans, cur);
				}

				if(have_CRDH_next(cur)){
					cur = get_CRDH_next(cur);
				}
				else{
					break;
				}
			}

		}

	}
		return ans;
}

