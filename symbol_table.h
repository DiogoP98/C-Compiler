#ifndef __sym_h__
#define __sym_h__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct _DataItem {
   char* key;
   int type; //int,float, char,....
};

struct _ItemsList {
    struct _DataItem* item;
    struct _ItemsList* next;
};

typedef struct _DataItem DataItem;
typedef struct _ItemsList ItemsList;

DataItem* createItem(char* name, int type, int endr);
bool checkExistence(char* name, ItemsList* list);
DataItem* head(ItemsList* l);
ItemsList* tail(ItemsList* l);

#endif
