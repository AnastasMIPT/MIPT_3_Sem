#include <cstdio>
#include "Sorts.h"
#include "MyInteger.h"
#include "../MyLib/my_vector.h"

using MyType = Numeric<int>;

template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);


template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;



Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (int i = 0; i < size; ++i) {
        vec[i] = rand () % 1024;
    }
    return vec;
}


template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size = 10, size_t delta = 10, size_t max_size = 100) {
    size_t size = start_size;
    Vector<Vector<size_t>> result;
    while (size <= max_size)
    {
        Vector<MyType> arr (rand_vector (size));

        func_sort (&arr[0], 0, size);

        Vector<size_t> temp (3);
        temp[0] = size;
        temp[1] = MyType::num_of_comp ();
        temp[2] = MyType::num_of_assigns ();
        result.push_back (temp);
        
        MyType::num_of_comp_to_zero ();
        MyType::num_of_assigns_to_zero ();
        
        size += delta;
    }
    
    return result;
}


int main () {

    Vector<Vector<size_t>> result = CompGraph_of_sort (MergeSortRecursive<MyType>);
    printf ("MergeSort:\n");
    for (int i = 0; i < result.size (); ++i) {
        printf ("size = %lu, comp = %lu, assigns = %lu\n", result[i][0], result[i][1], result[i][2]);
    }

    Vector<Vector<size_t>> result2 = CompGraph_of_sort (MergeSortRecursive <MyType>);
    printf ("BubbleSort:\n");
    for (int i = 0; i < result.size (); ++i) {
        printf ("%lu;%lu\n", result2[i][0], result2[i][1]);
    }

    return 0;
}