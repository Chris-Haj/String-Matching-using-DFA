
#include <stdlib.h>
#include "pattern_matching.h"

int pm_init(pm_t *pat){
    if (!pat)
        return ERROR;
    pat->newstate=0;
    root(pat)= calloc(1,sizeof(pm_state_t));
    if(!root(pat))
        return ERROR;

    root(pat)->id = root(pat)->depth=0;
    root(pat)->_transitions=NULL;
    root(pat)->output=NULL;
    root(pat)->fail = NULL; //Root has no failure transition
    root(pat)->_transitions = calloc(1, sizeof(dbllist_t));
    dbllist_init(pat->zerostate->_transitions);
    if(!pat->zerostate->_transitions){
        free(pat->zerostate);
        free(pat);
        return ERROR;
    }

    return SUCCESS;
}

int pm_addstring(pm_t *pat,unsigned char *symbol, size_t n){

    if (!pat)
        return ERROR;
    if (n == 0)
        return SUCCESS;
    pm_state_t *startS = root(pat);
    pm_state_t *cur;

    for (int i=0;i<n;i++){
        if(!(cur = pm_goto_get(startS,symbol[i]))){
            pm_goto_set(startS,symbol[i],cur);
        }
        else{

        }

    }

    return SUCCESS;
}

int pm_makeFSM(pm_t *pat){


    return SUCCESS;
}

int pm_goto_set(pm_state_t *from_state,unsigned char symbol,pm_state_t *to_state){
    pm_labeled_edge_t *newEdge = (pm_labeled_edge_t *) calloc(1,sizeof(pm_labeled_edge_t));
    newEdge->label = symbol;
    from_state->_transitions;

}

pm_state_t* pm_goto_get(pm_state_t *state,unsigned char symbol){
    dbllist_t *ListOfState = state->_transitions;
    if(!ListOfState)
        return NULL;
    dbllist_node_t *curNode = dbllist_head(ListOfState);
    while (curNode){
        if (symbol == extractSymbolFromNode(curNode))
            return extractStateFromNode(curNode);
        curNode = dbllist_next(curNode);
    }
    return NULL;
}

dbllist_t* pm_fsm_search(pm_state_t *state,unsigned char *symbol,size_t size){


    return SUCCESS;
}

void pm_destroy(pm_t *pat){

}
