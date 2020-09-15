

#include <cstdio>

template <typename T>
class Numeric {
    
    static size_t num_assigns;
    static size_t num_comparisons;

public:
    T data;
    
    Numeric () = default;
    Numeric (const T& other);
    Numeric (const Numeric& other);

    Numeric& operator= (const Numeric& other);

    template <typename Type>
    friend bool operator< (const Numeric<Type>& first, const Numeric<Type>& second);

    template <typename Type>
    friend bool operator> (const Numeric<Type>& first, const Numeric<Type>& second);

    static size_t num_of_comp () {
        return num_comparisons;
    }

    static size_t num_of_assigns () {
        return num_assigns;
    }

    static void num_of_comp_to_zero () {
        num_comparisons = 0;
    }

    static size_t num_of_assigns_to_zero () {
        num_assigns = 0;
    }
};



template<typename T>
Numeric<T>& Numeric<T>::operator= (const Numeric<T>& other) {
        data = other.data;
        Numeric<T>::num_assigns++;
        return *this;
}

template<typename T>
bool operator< (const Numeric<T>& first, const Numeric<T>& second)
{
    Numeric<T>::num_comparisons++;
    return first.data < second.data;
}

template<typename T>
bool operator> (const Numeric<T>& first, const Numeric<T>& second)
{
    Numeric<T>::num_comparisons++;
    return first.data > second.data;
}




template <typename T>
Numeric<T>::Numeric (const T& other) {
    data = other;
}

template <typename T>
Numeric<T>::Numeric (const Numeric& other) {
    data = other.data;
}
