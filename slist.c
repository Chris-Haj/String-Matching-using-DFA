#include <stdlib.h>
#include <stdio.h>
#include "slist.h"

void dbllist_init(dbllist_t *list)  {
    if (!list)
        return;
    dbllist_head(list) = NULL;
    dbllist_tail(list) = NULL;
    dbllist_size(list) = 0;
}

void dbllist_destroy(dbllist_t *list,dbllist_destroy_t des){

    
    dbllist_node_t *curNode = dbllist_head(list);
    dbllist_node_t *next;
    while(curNode){
        next = dbllist_next(curNode);
        if (des == DBLLIST_FREE_DATA)
            free(dbllist_data(curNode));
        free(curNode);
        curNode = dbllist_next(curNode);
    }
    free(list);
}

int dbllist_append(dbllist_t *list,void *node){

    if(!list)
        return ERROR;

    int curSize = dbllist_size(list);
    //Create newNode and store node data inside it while setting next and prev pointers to NULL
    dbllist_node_t *newNode = (dbllist_node_t *) calloc(1,sizeof(dbllist_node_t));
    if (!newNode)
        return ERROR;

    dbllist_next(newNode) = NULL;
    dbllist_prev(newNode) = NULL;
    dbllist_data(newNode) = node;

    //If list is empty, set newNode as head and tail of list-
    if (curSize == 0){
        dbllist_head(list) = newNode;
        dbllist_tail(list) = newNode;
    }
    else{
        dbllist_node_t *lastNode = dbllist_tail(list); // Get tail of list
        dbllist_prev(newNode) = lastNode; // set the prev pointer of newNode to previous tail
        dbllist_next(lastNode) = newNode; //set the next pointer of previous tail to newNode
        dbllist_tail(list) = newNode; // set newNode as new tail of list
    }
    dbllist_size(list) = curSize+1; //increase list size by 1
    return SUCCESS;
}

int dbllist_prepend(dbllist_t *list,void *node){
    if(!list)
        return ERROR;

    int curSize = dbllist_size(list);
    //Create newNode and store node data inside it while setting next and prev pointers to NULL
    dbllist_node_t *newNode = (dbllist_node_t *) calloc(1,sizeof(dbllist_node_t));
    if (!newNode)
        return ERROR;

    dbllist_next(newNode) = NULL;
    dbllist_prev(newNode) = NULL;
    dbllist_data(newNode) = node;

    //If list is empty, set newNode as head and tail of list-
    if (curSize == 0){
        dbllist_head(list) = newNode;
        dbllist_tail(list) = newNode;
    }
    else{
        dbllist_node_t *firstNode = dbllist_head(list); // Get head of list
        dbllist_next(newNode) = firstNode; //Set next pointer of newNode to previous head
        dbllist_prev(firstNode) = newNode; //Set prev pointer of previous head to newNode
        dbllist_head(list) = newNode; // Set head of list to newPointer
    }
    dbllist_size(list) = curSize+1; //increase list size by 1
    return SUCCESS;
}

int dbllist_remove(dbllist_t *list, dbllist_node_t* node ,dbllist_destroy_t des){

}
