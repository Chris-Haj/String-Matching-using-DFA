#include <stdlib.h>
#include <stdio.h>
#include "dbllist.h"

#define alloc(type) (type *) malloc(sizeof(type))


void dbllist_init(dbllist_t *list) {
    if (!list) {
        return;
    }
    dbllist_head(list) = NULL;
    dbllist_tail(list) = NULL;
    dbllist_size(list) = 0;
}

void dbllist_destroy(dbllist_t *list, dbllist_destroy_t des) {

    dbllist_node_t *curNode = dbllist_head(list);
    dbllist_node_t *next;
    while (curNode) {
        next = dbllist_next(curNode);
        if (des == DBLLIST_FREE_DATA)
            free(dbllist_data(curNode));
        free(curNode);
        curNode = next;
    }
    free(list);
}

int dbllist_append(dbllist_t *list, void *node) {

    if (!list)
        return -1;

    int curSize = dbllist_size(list);
    //Create newNode and store node data inside it while setting next and prev pointers to NULL
    dbllist_node_t *newNode = alloc(dbllist_node_t);
    if (!newNode) {
        return -1;
    }
    dbllist_next(newNode) = NULL;
    dbllist_prev(newNode) = NULL;
    dbllist_data(newNode) = node;

    //If list is empty, set newNode as head and tail of list-
    if (curSize == 0) {
        dbllist_head(list) = newNode;
        dbllist_tail(list) = newNode;
    } else {
        dbllist_node_t *lastNode = dbllist_tail(list); // Get tail of list
        dbllist_prev(newNode) = lastNode; // set the prev pointer of newNode to previous tail
        dbllist_next(lastNode) = newNode; //set the next pointer of previous tail to newNode
        dbllist_tail(list) = newNode; // set newNode as new tail of list
    }
    dbllist_size(list) = curSize + 1; //increase list size by 1
    return 0;
}

int dbllist_prepend(dbllist_t *list, void *node) {
    if (!list)
        return -1;

    int curSize = dbllist_size(list);
    //Create newNode and store node data inside it while setting next and prev pointers to NULL
    dbllist_node_t *newNode = alloc(dbllist_node_t);
    if (!newNode)
        return -1;

    dbllist_next(newNode) = NULL;
    dbllist_prev(newNode) = NULL;
    dbllist_data(newNode) = node;

    //If list is empty, set newNode as head and tail of list-
    if (curSize == 0) {
        dbllist_head(list) = newNode;
        dbllist_tail(list) = newNode;
    } else {
        dbllist_node_t *firstNode = dbllist_head(list); // Get head of list
        dbllist_next(newNode) = firstNode; //Set next pointer of newNode to previous head
        dbllist_prev(firstNode) = newNode; //Set prev pointer of previous head to newNode
        dbllist_head(list) = newNode; // Set head of list to newPointer
    }
    dbllist_size(list) = curSize + 1; //increase list size by 1
    return 0;
}

int dbllist_remove(dbllist_t *list, dbllist_node_t *node, dbllist_destroy_t des) {

    if (!list || !node)
        return ERROR;
    if (des == DBLLIST_FREE_DATA)
        free(dbllist_data(node));

    if (node == dbllist_head(list))
        dbllist_head(list) = dbllist_next(node);
    else if (node == dbllist_tail(list))
        dbllist_tail(list) = dbllist_prev(node);
    else {
        dbllist_node_t *prev = dbllist_prev(node);
        dbllist_node_t *next = dbllist_next(node);
        dbllist_prev(next) = prev;
        dbllist_next(prev) = next;
    }
    free(node);
    dbllist_size(list)--;
    return SUCCESS;
}
