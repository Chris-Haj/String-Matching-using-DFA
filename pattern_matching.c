#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pattern_matching.h"

#define root(pat) pat->zerostate
#define SymbolFromNode(n) ((pm_labeled_edge_t *) dbllist_data(n))->label
#define StateFromNode(n) ((pm_labeled_edge_t *) dbllist_data(n))->state
#define alloc(type) (type *) malloc(sizeof(type))

int pm_init(pm_t *pat) {
    if (!pat)
        return ERROR;

    root(pat) = alloc(pm_state_t);
    if (!root(pat))
        return ERROR;
    pat->newstate = 0;
    root(pat)->id = root(pat)->depth = pat->newstate++;
    root(pat)->fail = NULL; //Root has no failure transition
    root(pat)->_transitions = alloc(dbllist_t);
    root(pat)->output = alloc(dbllist_t);
    dbllist_init(root(pat)->_transitions);
    dbllist_init(root(pat)->output);
    return SUCCESS;
}

int pm_addstring(pm_t *pat, unsigned char *symbol, size_t n) {

    if (!pat)
        return ERROR;
    if (n == 0)
        return SUCCESS;
    pm_state_t *startS = root(pat);
    pm_state_t *cur = startS, *prev = NULL, *next = NULL;
    for (int i = 0; i < n; i++) {
        prev = cur;
        cur = pm_goto_get(cur, symbol[i]); //Attempt to find state that label points to
        if (!cur) { //If state does not exist allocate memory for it and initialize its data
            next = alloc(pm_state_t);
            next->_transitions = alloc(dbllist_t);
            next->output = alloc(dbllist_t);
            dbllist_init(next->_transitions);
            dbllist_init(next->output);
            next->fail = NULL;
            //Call the pm goto set to create a new edge and state while also connecting the current state with the new one using the new edge
            if (pm_goto_set(prev, symbol[i], next) == ERROR)
                return ERROR;
            cur = next;
            cur->depth = prev->depth + 1;
            cur->id = pat->newstate++;
            printf("%u\n", cur->id);
        }
    }
    //copy the input into our new char * so we can free it in the end.
    unsigned char *output = (unsigned char *) malloc((n + 1) * sizeof(unsigned char));
    memcpy(output, symbol, n + 1);
    if (dbllist_append(cur->output, output) == ERROR)
        return ERROR;
    return SUCCESS;
}


void FailureBetween(pm_state_t *root, pm_state_t *father, unsigned char symbol, pm_state_t *child) {
    pm_state_t *failure = pm_goto_get(father,symbol);
    if (failure){
        child->fail = failure;
        printf("Setting f(%u) = %u\n",child->id, failure->id);
    }
    else
        child->fail = root;
}

int pm_makeFSM(pm_t *pat) {

    if (!pat || !root(pat) || !root(pat)->_transitions)
        return ERROR;
    pm_state_t *root = root(pat);
    dbllist_t *list = root->_transitions;
    dbllist_t *stateHolder = alloc(dbllist_t); // StateHolder will be used as queue to go through the states level by level (BFS)
    dbllist_init(stateHolder);
    dbllist_node_t *curNode = dbllist_head(list);
    while (curNode) { //Loop to insert all states with depth = 1
        pm_state_t *state = StateFromNode(curNode);
        dbllist_append(stateHolder, state);
        state->fail = root;
        curNode = dbllist_next(curNode);
    }
    dbllist_node_t *queue = dbllist_head(stateHolder);
    while (queue) { //Loop to go through queue
        pm_state_t *curState = (pm_state_t *) dbllist_data(queue);
        dbllist_node_t *ChildrenStates = dbllist_head(curState->_transitions); //If curState has no transitions, ChildrenStates = NULL.
        while (ChildrenStates) { //Visit children of current state (head of queue)
            FailureBetween(root, curState->fail, SymbolFromNode(ChildrenStates), StateFromNode(ChildrenStates)); //Connect between failure of current State and child state if failure requirements apply
            dbllist_append(stateHolder, StateFromNode(ChildrenStates)); //Add children states of current state to queue
            ChildrenStates = dbllist_next(ChildrenStates);
        }
        queue = dbllist_next(queue);
        dbllist_remove(stateHolder,dbllist_head(stateHolder), DBLLIST_LEAVE_DATA); // Pop head of queue
    }
    free(stateHolder);
    return SUCCESS;
}

int pm_goto_set(pm_state_t *from_state, unsigned char symbol, pm_state_t *to_state) {
    if (!from_state || !from_state->_transitions) //If the state doesn't exist or has no transitions return error
        return ERROR;
    dbllist_t *listOfState = from_state->_transitions;
    //Create new edge and initialize its data
    pm_labeled_edge_t *newEdge = alloc(pm_labeled_edge_t);
    newEdge->state = to_state;
    newEdge->label = symbol;
    if (dbllist_append(listOfState, newEdge) == ERROR)
        return ERROR;
    printf("%u -> %c -> ", from_state->id, symbol);
    return SUCCESS;
}

pm_state_t *pm_goto_get(pm_state_t *state, unsigned char symbol) {
    if (!state || !state->_transitions) //If state or list of transitions is NULL
        return NULL;
    dbllist_t *ListOfState = state->_transitions;
    dbllist_node_t *curNode = dbllist_head(ListOfState);
    while (curNode) { //Search through transitions list for wanted symbol if found, return state
        if (symbol == SymbolFromNode(curNode))
            return StateFromNode(curNode);
        curNode = dbllist_next(curNode);
    }
    return NULL; //return NULL if no state was found.
}

dbllist_t *pm_fsm_search(pm_state_t *state, unsigned char *symbol, size_t size) {

    return SUCCESS;
}

void destroyer(pm_state_t *state) { //Recursion function to destroy all tree
    if (state->_transitions) { //Base case for when to continue recursion calls
        dbllist_node_t *stateNode = dbllist_head(state->_transitions); //Get first node of transitions
        dbllist_destroy(state->output, DBLLIST_FREE_DATA);//Free the output list of current state
        dbllist_node_t *next;

        while (stateNode) { //Loop through all nodes of transitions list that contain edges that contain pointers to next states
            pm_state_t *child = StateFromNode(stateNode); //Use macro to get state from current node
            destroyer(child); //Start recursive calls of child states
            free(dbllist_data(stateNode)); //After finishing recursive calls we start freeing up data of children states
            next = dbllist_next(stateNode);
            free(stateNode);
            stateNode = next;
        }
        free(state->_transitions); //Free list
    }
    free(state); //Free current state
}

void pm_destroy(pm_t *pat) {
    destroyer(pat->zerostate);
}