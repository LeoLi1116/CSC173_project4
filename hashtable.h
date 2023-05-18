

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

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


typedef struct hashtable* hashtable;



extern hashtable new_hashtable();
extern void set_first(hashtable table, int key, void* data);

extern void remove_CSG(hashtable table, CSG this);
extern void insertCSG(hashtable table, CSG a);
extern int CSGintable(hashtable table, CSG a);
extern void deleteCSG(hashtable table, char* course, int sid, char* grade);
extern LinkedList lookupCSG(hashtable table, char* course, int sid, char* grade);

extern void remove_SNAP(hashtable table, SNAP a);
extern void insertSNAP(hashtable table, SNAP a);
extern int SNAPintable(hashtable table, SNAP a);
extern void deleteSNAP(hashtable table, int sid, char* name, char* adress, int phone);
extern LinkedList lookupSNAP(hashtable table, int sid, char* name, char* adress, int phone);

extern int CPkey(CP a);
extern void remove_CP(hashtable table, CP this);
extern void insertCP(hashtable table, CP a);
extern int CPintable(hashtable table, CP a);
extern void deleteCP(hashtable table, char* class, char* pre);
extern LinkedList lookupCP(hashtable table, char* class, char* pre);

extern int CDHkey(CDH a);
extern void remove_CDH(hashtable table, CDH this);
extern void insertCDH(hashtable table, CDH a);
extern int CDHintable(hashtable table, CDH a);
extern void deleteCDH(hashtable table, char* class, char* day, char* hour);
extern LinkedList lookupCDH(hashtable table, char* class, char* day, char* hour);

extern int CRkey(CR a);
extern void remove_CR(hashtable table, CR this);
extern void insertCR(hashtable table, CR a);
extern int CRintable(hashtable table, CR a);
extern void deleteCR(hashtable table, char* class, char* room);
extern LinkedList lookupCR(hashtable table, char* class, char* room);

extern int CRDHkey(CRDH a);
extern void insertCRDH(hashtable table, CRDH a);
extern int CRDHintable(hashtable table, CRDH a);
extern LinkedList lookupCRDH(hashtable table, char* room);


#endif /* HASHTABLE_H_ */
