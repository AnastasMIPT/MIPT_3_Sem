#ifndef SORTS_H
#define SORTS_H

#include <cstdio>
#include <algorithm>

template <typename T>
void BubbleSort (T* arr, size_t left, size_t right) {
    size_t size = right - left;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i; j < size; ++j) {
            if (arr[i] > arr[j]) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}






template <typename T>
void Merge (T* arr, size_t left, size_t mid, size_t right) {
    size_t it1 = 0;
    size_t it2 = 0;
    T result[right - left];
 
    while (left + it1 < mid && mid + it2 < right) {
        if (arr[left + it1] < arr[mid + it2]) {
            result[it1 + it2] = arr[left + it1];
            it1 += 1;
            
        } else {
            result[it1 + it2] = arr[mid + it2];
            it2 += 1;
        }
    }
    while (left + it1 < mid) {
        result[it1 + it2] = arr[left + it1];
        it1 += 1;
        
    }
 
    while (mid + it2 < right) {
        result[it1 + it2] = arr[mid + it2];
        it2 += 1;
    }
 
    for (size_t i = 0; i < it1 + it2; ++i)
        arr[left + i] = result[i];
}


template <typename T>
void MergeSortRecursive (T* arr, size_t left, size_t right) {
    if (left + 1 >= right)
        return;

    size_t mid = (left + right) / 2;
    MergeSortRecursive (arr, left, mid);
    MergeSortRecursive (arr, mid, right);
    Merge (arr, left, mid, right);
}

















#endif // SORTS_H