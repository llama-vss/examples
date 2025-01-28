#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdint.h>
#include "generic.h"

typedef enum{
    LINK_INIT,
    LINK_SINGLE,
    LINK_DOUBLE,
    LINK_QUAN
}LinkListType_t;

typedef enum{
    SORT_BUBBLE,
    SORT_SELECTION,
    SORT_QUICK,
    SORT_INSERTION,
    SORT_MERGE,
    SORT_QUAN
}SortType_t;

//This only allows for one instance of the linked list to exsists
//Not thread safe

//Init
//Type select
bool ll_init(LinkListType_t type);
//Deinit
bool ll_deinit();
//Add to end
bool ll_add(int value);
//Remove at position, returns the value
bool ll_remove(uint32_t index, int32_t * value);
//Sort
//Search, returns index of the first instance
bool ll_search(uint32_t * index, int32_t value);
//Insert at position
bool ll_insert(uint32_t index, int32_t value);
//Print list
void ll_print();

#endif