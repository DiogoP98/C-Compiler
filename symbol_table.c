#include "symbol_table.h"


DataItem* createItem(char* name, int type, int endr) {
    DataItem* node = (DataItem*) malloc(sizeof(DataItem));
    node->key = strdup(name);
    node->type = type;

    return node;
}

bool checkExistence(char* name, ItemsList* list) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));

    item = head(list);

    while(item != NULL) {
        if(item->key == name) return true;

        list = tail(list);
        item = head(list);
    }

    return false;
}

DataItem* head(ItemsList* l) {
    return l->item;
}

ItemsList* tail(ItemsList* l) {
    return l->next;
}


