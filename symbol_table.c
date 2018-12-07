#include "symbol_table.h"
#include <string.h>


ItemsList* createItem(ItemsList* list, char* name, int type) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));
    ItemsList* node = (ItemsList*) malloc(sizeof(ItemsList));
    strcpy(item->key, name);
    item->type = type;

    node = mkList2(item, list);

    printf("insert %s\n", item->key);

    return node;
}

int checkExistence(char* name, ItemsList* list) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));

    item = head2(list);

    while(item != NULL) {
        printf("procura %s\n", item->key);
        if(strcmp(item->key,name)==0) return item->type;

        list = tail2(list);
        item = head2(list);
    }

    return -1;
}

void printTable(ItemsList* list) {
    DataItem *item = list->item;

    while(item != NULL){
        printf("ola - %s\n", item->key);
        list = list->next;
        item = list->item;
    }
}

DataItem* head2(ItemsList* l) {
    if(l == NULL)
        return NULL;

    return l->item;
}

ItemsList* tail2(ItemsList* l) {
    return l->next;
}

ItemsList* mkList2(DataItem* item, ItemsList* list) {
    ItemsList* node = (ItemsList*) malloc(sizeof(ItemsList));
    node->item = item;
    node->next = list;
    return node;
}


