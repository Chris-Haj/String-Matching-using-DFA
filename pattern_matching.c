
#include <stdlib.h>
#include "pattern_matching.h"

int pm_init(pm_t *pat) {
    if (!pat)
        return ERROR;
    pat->newstate = 0;
    root(pat) = calloc(1, sizeof(pm_state_t));
    if (!root(pat))
        return ERROR;

    pat->newstate = 0;
    root(pat)->id = root(pat)->depth = pat->newstate++;
    root(pat)->fail = NULL; //Root has no failure transition
    root(pat)->_transitions = NULL;
    root(pat)->output = NULL;
    return SUCCESS;
}

int pm_addstring(pm_t *pat, unsigned char *symbol, size_t n) {

    if (!pat)
        return ERROR;
    if (n == 0)
        return SUCCESS;
    pm_state_t *startS = root(pat);
    pm_state_t *cur = startS, *prev,*next;
    for (int i = 0; i < n; i++) {
        prev = cur;
        cur = pm_goto_get(cur,symbol[i]);
        if(!cur){
            pm_goto_set(prev,symbol[i],next);
            cur = (pm_state_t *) prev->_transitions->tail->data;
            cur->depth = prev->depth+1;
            cur->id = root(pat)->id++;
            cur->_transitions=NULL;
            cur->output=NULL;
            cur->fail=NULL;
        }
    }

    return SUCCESS;
}

int pm_makeFSM(pm_t *pat) {


    return SUCCESS;
}

int pm_goto_set(pm_state_t *from_state, unsigned char symbol, pm_state_t *to_state) {
    dbllist_t *listOfState = from_state->_transitions;
    if(!listOfState){
        from_state->_transitions = alloc(dbllist_t);
        dbllist_init(listOfState);
    }
    pm_labeled_edge_t *newEdge = alloc(pm_labeled_edge_t);
    newEdge->state = alloc(pm_state_t);
    newEdge->label = symbol;
    dbllist_append(listOfState,newEdge);
    to_state = newEdge->state;


}

pm_state_t *pm_goto_get(pm_state_t *state, unsigned char symbol) {
    dbllist_t *ListOfState = state->_transitions;
    if (!ListOfState)
        return NULL;
    dbllist_node_t *curNode = dbllist_head(ListOfState);
    while (curNode) {
        if (symbol == SymbolFromNode(curNode))
            return StateFromNode(curNode);
        curNode = dbllist_next(curNode);
    }
    return NULL;
}

dbllist_t *pm_fsm_search(pm_state_t *state, unsigned char *symbol, size_t size) {


    return SUCCESS;
}

void pm_destroy(pm_t *pat) {

}
