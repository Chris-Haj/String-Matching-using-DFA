#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern_matching.h"
#define alloc(type) (type *) malloc(sizeof(type))


int main() {

    pm_t *tree = alloc(pm_t);
    pm_init(tree);
    unsigned char **strings = (unsigned char **) malloc(4*sizeof(unsigned char *));
    for(int i=0;i<4;i++){
        strings[i] = (unsigned char *) malloc(4*sizeof(unsigned char));
    }
    strcpy(strings[0],"abc");
    strcpy(strings[1],"bca");
    strcpy(strings[2],"cab");
    strcpy(strings[3],"acb");
    for (int i = 0; i < 4; ++i) {
        pm_addstring(tree,strings[i],strlen(strings[i]));
    }
    pm_makeFSM(tree);
    pm_destroy(tree);
    free(tree);
    for (int i = 0; i < 4; ++i) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
