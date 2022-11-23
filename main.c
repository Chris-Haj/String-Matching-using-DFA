#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern_matching.h"

int main() {

    dbllist_t *list = alloc(dbllist_t);
    pm_t *tree = alloc(pm_t);
    dbllist_init(list);
    pm_init(tree);
    unsigned char *string = calloc(3,sizeof(char));
    unsigned char *string2 = calloc(3,sizeof(char));
    strcpy(string,"ab");
    strcpy(string2,"cd");
    pm_addstring(tree,string,2);
    pm_addstring(tree,string2,2);
    return 0;
}
