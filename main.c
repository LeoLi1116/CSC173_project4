/*
 * main.c
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
#include "CRDH.h"
#include "CDH.h"
#include "CR.h"
#include "LinkedList.h"
#include "hashtable.h"



hashtable create_CSG_table(){
	CSG a = new_CSG("CSC101", 12345, "A");
	CSG b = new_CSG("CSC101", 67890, "B");
	CSG c = new_CSG("EE200", 12345, "C");
	CSG d = new_CSG("EE200", 22222, "B+");
	CSG e = new_CSG("CSC101", 33333, "A-");
	CSG f = new_CSG("PH100",67890, "C+");

	hashtable CSGtable = new_hashtable();

	insertCSG(CSGtable, a);
	insertCSG(CSGtable, b);
	insertCSG(CSGtable, c);
	insertCSG(CSGtable, d);
	insertCSG(CSGtable, e);
	insertCSG(CSGtable, f);

	return CSGtable;
}

hashtable create_SNAP_table(){
	SNAP a = new_SNAP(12345, "C. Brown", "12 Apple St.", 5551234);
	SNAP b = new_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", 5555678);
	SNAP c = new_SNAP(22222, "P. Patty", "56 Grape Blvd.", 5559999);
	hashtable SNAPtable = new_hashtable();
	insertSNAP(SNAPtable, a);
	insertSNAP(SNAPtable, b);
	insertSNAP(SNAPtable, c);

	return SNAPtable;
}

hashtable create_CP_table(){
	CP a = new_CP("CSC101","CSC100");
	CP b = new_CP("EE200","EE005");
	CP c = new_CP("EE200","CSC100");
	CP d = new_CP("CSC120","CSC101");
	CP e = new_CP("CSC121","CSC120");
	CP f = new_CP("CSC205","CSC101");
	CP g = new_CP("CSC206","CSC121");
	CP h = new_CP("CSC206","CSC205");
	hashtable CPtable = new_hashtable();
	insertCP(CPtable, a);
	insertCP(CPtable, b);
	insertCP(CPtable, c);
	insertCP(CPtable, d);
	insertCP(CPtable, e);
	insertCP(CPtable, f);
	insertCP(CPtable, g);
	insertCP(CPtable, h);
	return CPtable;
}

hashtable create_CDH_table(){

	CDH a = new_CDH("CSC101","M","9AM");
	CDH b = new_CDH("CSC101","W","9AM");
	CDH c = new_CDH("CSC101","F","9AM");
	CDH d = new_CDH("EE200","Tu","10AM");
	CDH e = new_CDH("EE200","W","1PM");
	CDH f = new_CDH("EE200","Th","10AM");
	hashtable CDHtable = new_hashtable();

	insertCDH(CDHtable, a);
	insertCDH(CDHtable, b);
	insertCDH(CDHtable, c);
	insertCDH(CDHtable, d);
	insertCDH(CDHtable, e);
	insertCDH(CDHtable, f);

	return CDHtable;
}

hashtable create_CR_table(){
	CR a = new_CR("CSC101","Turing Aud.");
	CR b = new_CR("EE200","25 Ohm Hall");
	CR c = new_CR("PH100","Newton Lab.");

	hashtable CRtable = new_hashtable();

	insertCR(CRtable, a);
	insertCR(CRtable, b);
	insertCR(CRtable, c);

	return CRtable;
}







void part1a(){
	hashtable CSGtable = create_CSG_table();
	printf("hash table created.\n");
	LinkedList ans = lookupCSG(CSGtable, "CSC101", 12345, "*");
	printf("look up grade for student id = 12345, course = CSC101.\n");
	if(LinkedList_isEmpty(ans) != true){
		printf("this student get %s in this class.\n",get_grade((CSG) LinkedList_pop(ans)));
	}
}

void part1b(){
	hashtable CPtable = create_CP_table();
	printf("hash table created.\n");
	LinkedList ans = lookupCP(CPtable, "CSC205", "CSC120");
	printf("Checking is CSC120 the prerequisite of CSC205\n");
	if(LinkedList_isEmpty(ans) != true){
		printf("result: CSC120 is the prerequisite for CSC205\n");
	}
	else{
		printf("result: CSC120 is not the prerequisite for CSC205\n");
	}


}

void part1c(){
	hashtable CRtable = create_CR_table();
	printf("hash table created.\n");
	LinkedList pre_deltetion = lookupCR(CRtable,"*","*");

	CR a;

	printf("print out everything from this table.\n");
	while(LinkedList_isEmpty(pre_deltetion) != true){

		a = (CR) LinkedList_pop(pre_deltetion);
		char* course = get_CR_class(a);
		char* room =   get_room(a);
		printf("course: %s, room: %s\n", course, room);
	}

	printf("print end.\n");
	printf("deleting course: \"CSC101\" from this hash table.\n");
	deleteCR(CRtable, "CSC101", "*");
	printf("deletion complete. \n");


	printf("print out everything from this table.\n");

	LinkedList after_deltetion = lookupCR(CRtable,"*","*");

	while(LinkedList_isEmpty(after_deltetion) != true){

		a = (CR) LinkedList_pop(after_deltetion);
		char* course = get_CR_class(a);
		char* room =   get_room(a);
		printf("course: %s, room: %s\n", course, room);

	}
	printf("print end.\n");
}

void part1d(){
	hashtable CPtable = create_CP_table();
	printf("hash table created.\n");
	printf("inserting CSC120 as CSC205's prerequisite.\n");
	CP new = new_CP("CSC205", "CSC120");
	insertCP(CPtable, new);
	LinkedList ans = lookupCP(CPtable, "CSC205", "CSC120");
	printf("Checking is CSC120 the prerequisite of CSC205.\n");
	if(LinkedList_isEmpty(ans) != true){
		printf("result: CSC120 is the prerequisite for CSC205.\n");
	}
	else{
		printf("result: CSC120 is not the prerequisite for CSC205.\n");
	}

}

void part1e(){
	hashtable CPtable = create_CP_table();
	printf("hash table created.\n");
	printf("inserting CSC101 as CSC205's prerequisite.\n");
	CP new = new_CP("CSC205", "CSC101");
	insertCP(CPtable, new);


}

void part1(){

	printf("Demonstrate part 1 by executing example in 8.2\n");

	printf("part a:\n");
	part1a();
	printf("\n part b:\n");
	part1b();
	printf("\n part c:\n");
	part1c();
	printf("\n part d:\n");
	part1d();
	printf("\n part e:\n");
	part1e();
	printf("\n part 1 end.\n");

}

void part2_1 (char* name, char* course){
	hashtable SNAPtable = create_SNAP_table();
	hashtable CSGtable = create_CSG_table();

	LinkedList sidlist = lookupSNAP(SNAPtable, -1, name, "*", -1);


		if(LinkedList_isEmpty(sidlist) != true){
			SNAP ans = (SNAP) LinkedList_pop(sidlist);
			int sid = get_SNAP_sid(ans);

			freeSNAP(ans);

			LinkedList gradelist = lookupCSG(CSGtable, course, sid, "*");

			if(LinkedList_isEmpty(gradelist) != true){
				char* grade = get_grade(LinkedList_pop(gradelist));
				printf("%s get %s in %s\n", name, grade, course);
				return;
			}
			else{
				printf("There is no student named %s in %s\n", name, course);
				return;
			}
		}


	printf("There is no student named %s\n", name);

}

void part2_2(char* name, char* day, char* hour){

	hashtable SNAPtable = create_SNAP_table();
	hashtable CSGtable = create_CSG_table();
	hashtable CDHtable = create_CDH_table();
	hashtable CRtable = create_CR_table();

	LinkedList sidlist = lookupSNAP(SNAPtable, -1, name, "*", -1);

	if(LinkedList_isEmpty(sidlist) != true){
		SNAP ans = (SNAP) LinkedList_pop(sidlist);
		int sid = get_SNAP_sid(ans);
		freeSNAP(ans);

		LinkedList courselist = lookupCSG(CSGtable, "*", sid, "*");

		while(LinkedList_isEmpty(courselist) != true){

			CSG course = (CSG) LinkedList_pop(courselist);
			char* course_name = get_course(course);
			freeCSG(course);
			LinkedList dayhourlist = lookupCDH(CDHtable, course_name, day, hour);

			while(LinkedList_isEmpty(dayhourlist) != true){

				CDH dayhour = LinkedList_pop(dayhourlist);
				char* course_DH = get_CDH_class(dayhour);
				free(dayhour);

				LinkedList roomlist = lookupCR(CRtable, course_DH, "*");

				if(LinkedList_isEmpty(roomlist) != true){
					CR for_room = (CR) LinkedList_pop(roomlist);
					char* room = get_room(for_room);
					freeCR(for_room);
					printf("%s is at %s on %s at %s\n", name, room, day, hour);

					return;
				}

			}

			printf("%s has no class on %s at %s\n", name, day, hour);
			return;

		}

	}

	printf("There is no student named %s\n", name);
}

void part2(){

	while(1){
		char name[256];
		char course[256];
		printf("%s\n", "Enter \"q\" to go to 2.2, or \"s\" to stay in 2.1: ");
		char command;
		scanf("%c%*c", &command);
		if(command == 'q') {
			printf("%s\n", "Exit");
			break;
		} else if (command == 's'){

			printf("enter the name for the student:\n");
			scanf("%[^\n]%*c", name);
			printf("enter the name for the course:\n");
			scanf("%[^\n]%*c", course);
			part2_1(name, course);
		}
	}

	while(1){
		char name[256];
		char day[256];
		char hour[256];
		printf("%s\n", "Enter \"q\" to go to part3, or \"s\" to stay in 2.2: ");
		char command;
		scanf("%c%*c", &command);
		if(command == 'q') {
			printf("%s\n", "Exit");
			break;
		} else if (command == 's'){
			printf("enter the name for the student:\n");
			scanf("%[^\n]%*c", name);
			printf("enter the day of week:\n");
			scanf("%[^\n]%*c", day);
			printf("enter the hour of the day:\n");
			scanf("%[^\n]%*c", hour);
			part2_2(name, day, hour);
		}
	}



}


hashtable selectCSG(hashtable CSGtable, char* course){
	LinkedList match = lookupCSG(CSGtable, course, -1, "*");
	hashtable select = new_hashtable();

	while(LinkedList_isEmpty(match) != true){
		CSG a = (CSG) LinkedList_pop(match);
		char* course = get_course(a);
		int sid = get_sid(a);
		char* grade = get_grade(a);
		printf("%s %d %s\n", course, sid, grade);
		insertCSG(select, a);
	}

	return select;
}

LinkedList project_sid(hashtable CSGtable){
	LinkedList all = lookupCSG(CSGtable, "*", -1, "*");
	LinkedList ans = new_LinkedList();

	while(LinkedList_isEmpty(all) != true){
		CSG a = (CSG) LinkedList_pop(all);
		int sid = get_sid(a);
		if(LinkedList_contains(ans, (void*) sid) == false){
		printf("%d\n", sid);
		LinkedList_add_at_end(ans, (void*) sid);
		}
	}

	return ans;
}

hashtable join_CR_CDH(hashtable CRtable, hashtable CDHtable){
	LinkedList CDHlist = lookupCDH(CDHtable,"*","*", "*");
	hashtable CRDHtable = new_hashtable();

	while(LinkedList_isEmpty(CDHlist) != true){
		CDH cur = (CDH) LinkedList_pop(CDHlist);

		char* class = get_CDH_class(cur);
		char* day = get_day(cur);
		char* hour = get_hour(cur);
		CR getRoom = (CR) LinkedList_pop(lookupCR(CRtable, class, "*"));
		char* room = (char*) get_room(getRoom);

		printf("%s %s %s %s\n", class, room, day, hour);

		CRDH new = new_CRDH(class, room, day, hour);

		insertCRDH(CRDHtable, new);

	}

	return CRDHtable;

}

hashtable selectRoom(hashtable CRDHtable, char* room){
	LinkedList match = lookupCRDH(CRDHtable, room);
	hashtable select = new_hashtable();

	while(LinkedList_isEmpty(match) != true){
		CRDH a = (CRDH) LinkedList_pop(match);
		char* course = get_CRDH_class(a);
		char* room = get_CRDH_room(a);
		char* day = get_CRDH_day(a);
		char* hour = get_CRDH_hour(a);
		printf("%s %s %s %s\n", course, room, day, hour);
		insertCRDH(select, a);
	}

	return select;
}

LinkedList project_DH(hashtable table){
	LinkedList ans = new_LinkedList();
	LinkedList use = lookupCRDH(table, "*");

	while(LinkedList_isEmpty(use) != true){
		CRDH a = (CRDH) LinkedList_pop(use);
		char* day = get_CRDH_day(a);
		char* hour = get_CRDH_hour(a);


		printf("%s %s\n", day, hour);
		LinkedList_add_at_end(ans, day);
		LinkedList_add_at_end(ans, hour);
	}




	return ans;
}


void part3(){

	printf("8.12 example: selection Operator\n selecting course = CSC101 from CSG table\n");
	hashtable ans = selectCSG(create_CSG_table(), "CSC101");
	printf("selection complete\n \n");

	printf("8.13 example: project student id for students who taking CSC101:\n");
	project_sid(ans);
	printf("projection complete\n \n");

	printf("8.14 example: join CR and CDH:\n \n");
	hashtable c = join_CR_CDH(create_CR_table(), create_CDH_table());
	printf("join complete\n \n");

	printf("8.15 example: \n");
	printf("selecting course in Turing Aud. \n");
	hashtable d = selectRoom(c, "Turing Aud.");
	printf("selection complete\n");
	printf("project their day and hour\n");
	project_DH(d);
	printf("projection complete");

}



int main(int argc, char *argv[]) {

	hashtable a = create_CR_table();
	hashtable b = create_CDH_table();
	hashtable CSGtable = create_CSG_table();


	part1();
	part2();
	part3();

	printf("\n end\n");
}

