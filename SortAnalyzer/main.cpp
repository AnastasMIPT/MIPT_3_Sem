#include <cstdio>
#include "Sorts.h"

int main () {

    int* a = new int [10];
    for (int i = 0; i < 10; ++i) {
        a[i] = -i;
    }


    MergeSortRecursive (a, 0, 10);
    
    for (int i = 0; i < 10; ++i) {
        printf ("%d ", a[i]);
    }
    printf ("\n");

    delete a;
    return 0;
}