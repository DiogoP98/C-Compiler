#include "symbol_table.h"


ItemsList* createItem(ItemList* list, char* name, int type) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));
    ItemsList* node = (ItemsList*) malloc(sizeof(ItemsList));
    item->key = strdup(name);
    item->type = type;

    node = mklist(item, list);

    return node;
}

int checkExistence(char* name, ItemsList* list) {
    DataItem* item = (DataItem*) malloc(sizeof(DataItem));

    item = head(list);

    while(item != NULL) {
        if(strcmp(item->key,name)==0) return item->type;

        list = tail(list);
        item = head(list);
    }

    return -1;
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


