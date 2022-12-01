#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern_matching.h"
#define alloc(type) (type *) malloc(sizeof(type))


int main() {

    pm_t *tree = alloc(pm_t);
    pm_init(tree);
    unsigned char **strings = (unsigned char **) malloc(6*sizeof(unsigned char *));
    for(int i=0;i<6;i++){
        strings[i] = (unsigned char *) malloc(8*sizeof(unsigned char));
    }
    strcpy(strings[0],"e");
    strcpy(strings[1],"be");
    strcpy(strings[2],"bd");
    strcpy(strings[3],"bcd");
    strcpy(strings[4],"cdbcab");
    strcpy(strings[5],"bcaa");
    for (int i = 0; i < 6; ++i) {
        pm_addstring(tree,strings[i],strlen(strings[i]));
    }
    pm_makeFSM(tree);
    pm_destroy(tree);
    free(tree);
    for (int i = 0; i < 6; ++i) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
