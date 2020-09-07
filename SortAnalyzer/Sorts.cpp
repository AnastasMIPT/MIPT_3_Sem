#include <stdio.h>
#include "Sorts.h"






template <typename T>
void MergeSortRecursive (T* a, size_t left, size_t right) {
    if (left + 1 >= right)
        return;

    size_t mid = (left + right) / 2;
    MergeSortRecursive (a, left, mid);
    MergeSortRecursive (a, mid, right);
    Merge (a, left, mid, right);
}

template <typename T>
void Merge (T* a, size_t left, size_t mid, size_t right) {
    size_t it1 = 0;
    size_t it2 = 0;
    T result[right - left];
 
    while (left + it1 < mid && mid + it2 < right) {
        if (a[left + it1] < a[mid + it2]) {
            result[it1 + it2] = a[left + it1];
            it1 += 1;
            
        } else {
            result[it1 + it2] = a[mid + it2];
            it2 += 1;
        }
    }
    while (left + it1 < mid) {
        result[it1 + it2] = a[left + it1];
        it1 += 1;
        
    }
 
    while (mid + it2 < right) {
        result[it1 + it2] = a[mid + it2];
        it2 += 1;
    }
 
    for (size_t i = 0; i < it1 + it2; ++i)
        a[left + i] = result[i];
}