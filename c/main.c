
#include <stdio.h>
#include "lib/ringbuffer_array.h"
#include "lib/linkedlist.h"

#define LINKED_LIST_ELEMENT_SIZE 5
#define LINKED_LIST_REMOVE_ELEMENT_INDEX 4
#define LINKED_LIST_FIND_VALUE 2
#define LINKED_LIST_INSERT_VALUE 5
#define LINKED_LIST_INSERT_INDEX 0

int main(){

    int32_t value = 0;
    uint32_t index = 0;

    //Begin test of single linked list
    printf("Start Single Linked List\n");
    ll_init(LINK_SINGLE);
    for(uint8_t iter = 0; iter < LINKED_LIST_ELEMENT_SIZE; iter++){
        ll_add(iter);
    }
    //ll_print();
    ll_remove(LINKED_LIST_REMOVE_ELEMENT_INDEX, &value);
    ll_print();
    
    if(ll_search(&index, LINKED_LIST_FIND_VALUE)){
        printf("Found %d at location %d\n", LINKED_LIST_FIND_VALUE, index);
    }else{
        printf("Not in list\n");
    }

    ll_deinit();

    printf("End Single Linked List\n\n\n\n");
    //Begin test of double linked list
    
    ll_init(LINK_DOUBLE);
    
    for(uint8_t iter = 0; iter < LINKED_LIST_ELEMENT_SIZE; iter++){
        ll_add(iter);
    }
    //ll_print();
    ll_remove(LINKED_LIST_REMOVE_ELEMENT_INDEX, &value);
    ll_print();
    if(ll_search(&index, LINKED_LIST_FIND_VALUE)){
        printf("Found %d at location %d\n", LINKED_LIST_FIND_VALUE, index);
    }else{
        printf("Not in list\n");
    }

    printf("---------------\n\n\n\n");
    if(ll_insert(LINKED_LIST_INSERT_INDEX, LINKED_LIST_INSERT_VALUE)){
        ll_print();
    }else{
        printf("Insert failed\n");
    }

    ll_deinit();
    return 0;
}