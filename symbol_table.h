#ifndef __ast_h__
#define __ast_h__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct DataItem {
   int data; 

    union {  
        int key;
        char ckey;
    } keys;
};

struct DataItem* array; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key);
struct DataItem* search(int key);
void insert(int key,int data);
struct DataItem* deleteItem(struct DataItem* item);

#endif