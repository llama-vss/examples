#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

typedef struct node{
    int32_t value;
    struct node * next;
    struct node * prev;
}Node_t;

static LinkListType_t list_type = LINK_INIT;
static Node_t * head = NULL;
static Node_t * end = NULL;

bool is_empty(){
    if(head == NULL){
        return TRUE;
    }
    return FALSE;
}

bool ll_init(LinkListType_t type){
    if((type < LINK_INIT) || (type > LINK_QUAN)){
        return FALSE;
    }
    if(head != NULL){
        return FALSE;
    }
    head = NULL;
    end = NULL;
    list_type = type;
    return TRUE;
}

bool ll_deinit(){
    //If stuff exsists then clean it up
    if(!is_empty()){
        //Cursor used to store the current head
        Node_t * cursor = head;
        //The next element in the linked list
        Node_t * next = head;
        //Continue until we get to the end of the nodes
        while(cursor->next != NULL){
            //Save the location for the next node
            next = cursor->next;
            //Free the current node
            free(cursor);
            //Move to the next node
            cursor = next;
        }
        //Last node to be cleaned up
        free(cursor);
    }
    //Do not save the list type
    list_type = LINK_INIT;
    //Reset the head
    head = NULL;
    //Reset the end position
    end = NULL;
    //Completed
    return TRUE;
}

bool ll_add(int value){
    //Allocate one node of size
    Node_t * temp = malloc(sizeof(Node_t));
    
    //Make sure that allocation worked
    if(temp == NULL){
        return FALSE;
    }

    //Special case for the first item being added
    if(is_empty()){
        head = temp;
        end = temp;
        temp->value = value;
        temp->prev = NULL;
        temp->next = NULL;
        return TRUE;
    }
    //Point the end to the new element
    end->next = temp;
    //Check to see if this is a double linked list
    if(list_type == LINK_DOUBLE){
        temp->prev = end;
    }else{
        temp->prev = NULL;
    }
    //Save the value
    temp->value = value;
    //Since this is the end node mark the next as null
    temp->next = NULL;
    //Save the position of the end
    end = temp;
}

bool ll_remove(uint32_t index, int32_t * value){
    //If empty then return right away
    if(is_empty()){
        return FALSE;
    }
    //No list init
    if(list_type == LINK_INIT){
        return FALSE;
    }

    //Take care of the case where there is only one element
    if(head->next == NULL){
        free(head);
        head = NULL;
        end = NULL;
        return TRUE;
    }

    Node_t * cursor = head;
    Node_t * last = head;
    for(uint32_t iter = 0; iter < index; iter++){
        //check to see if there are no more elements
        if(cursor == NULL){
            //We got to the end, not enough items
            return FALSE;
        }
        last = cursor;
        cursor = cursor->next;
    }
    if(list_type == LINK_SINGLE){
        last->next = cursor->next;
        //If the next node is the end then update the pointer to the end
        if(cursor->next == NULL){
            end = last;
        }else if(last == cursor){
            head = cursor->next;
        }
    }else if(list_type == LINK_DOUBLE){
        //We are at the head
        if(cursor->prev == NULL){
            head = cursor->next;
        }else{
            //We are not at the head
            cursor->prev->next = cursor->next;
        }
        //Only update the previous on the next one if it exsists
        if(cursor->next == NULL){
            end = cursor;
        }else{
            //Just remove the previous item
            cursor->next->prev = cursor->prev;
        }
    }
    *value = cursor->value;
    free(cursor);
    return TRUE;
}

bool ll_search(uint32_t * index, int32_t value){
    if(is_empty()){
        return FALSE;
    }
    Node_t * cursor = head;
    uint32_t place = 0;

    while(cursor->next != NULL){
        if(cursor->value == value){
            *index = place;
            return TRUE;
        }
        place++;
        cursor = cursor->next;
    }
    return FALSE;
}

bool ll_insert(uint32_t index, int32_t value){
    Node_t * cursor = head;
    Node_t * last = head;
    for(uint32_t iter = 0; iter < index; iter++){
        if(cursor == NULL){
            //Cannot insert at desired location
            return FALSE;
        }
        //Move to the next element
        last = cursor;
        cursor = cursor->next;
    }

    Node_t * new_data = malloc(sizeof(Node_t));
    new_data->value = value;

    //Nothing in the array
    if(is_empty()){
        head = new_data;
        head->next = NULL;
        head->prev = NULL;
        end = new_data;
        return TRUE;
    }

    if(index == 0){
        //Inserting at head condition
        head = new_data;
        head->next = cursor;
        if(list_type == LINK_DOUBLE){
            head->prev = NULL;
        }
    }else{
        //Inserting elsewhere
        Node_t * temp;
        new_data->next = last->next;
        if(list_type == LINK_DOUBLE){
            if(cursor != NULL){
                cursor->next->prev = new_data;
            }else{
                end = new_data;
            }
            new_data->prev = last;
        }
        last->next = new_data;
    }
    return TRUE;

}

void ll_print(){
    //Check if the list is empty
    if(is_empty()){
        printf("Linked list is empty\n");
        return;
    }
    //Use a cursor to walk through the list
    Node_t * cursor = head;
    do{
        printf("----\nThe value is %d\n", cursor->value);
        printf("The current memory address is %p\n", (void*)cursor);
        printf("The next memory address is %p\n", (void*)cursor->next);
        if(list_type == LINK_DOUBLE){
            printf("The previous memory address is %p\n", (void*)cursor->prev);
        }
        //Move to the next element
        cursor = cursor->next;
    }while(cursor != NULL);
    printf("----\n");
}

