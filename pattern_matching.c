
#include "pattern_matching.h"

int pm_init(pm_t *pat){


    return 0;
}

int pm_addstring(pm_t *pat,unsigned char *symbol, size_t n){


    return 0;
}

int pm_makeFSM(pm_t *pat){


    return 0;
}

int pm_goto_set(pm_state_t *from_state,unsigned char symbol,pm_state_t *to_state){


    return 0;
}

pm_state_t* pm_goto_get(pm_state_t *state,unsigned char symbol){


    return 0;
}

dbllist_t* pm_fsm_search(pm_state_t *state,unsigned char *symbol,size_t size){


    return 0;
}

void pm_destroy(pm_t *pat){

}
