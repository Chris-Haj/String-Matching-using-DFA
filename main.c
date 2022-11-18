#include <stdio.h>
#include <stdlib.h>


int main() {

    int *test;
    test = (int *) calloc(1,sizeof(int));
    *test = 3;
    printf("%d %d",sizeof(test),*test);


    return 0;
}
