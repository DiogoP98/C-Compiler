#include "symbol_table.h"


DataItem* createItem(char* name, int type, int endr) {
    DataItem* node = (DataItem*) malloc(sizeof(DataItem));
    node->key = strdup(name);
    node->type = type;

    return node;
}

DataItem* checkExistence(char* name, ItemsList* list) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));

    item = head(list);

    while(item != NULL) {
        if(item->key == name) return item;

        list = tail(list);
        item = head(list);
    }

    return NULL;
}

DataItem* head(ItemsList* l) {
    return l->item;
}

ItemsList* tail(ItemsList* l) {
    return l->next;
}

ItemsList* mkList(DataItem* item, ItemsList* list) {
    ItemsList* node = (ItemsList*) malloc(sizeof(ItemsList));
    node->instruction = item;
    node->next = l;
    return node;
}


