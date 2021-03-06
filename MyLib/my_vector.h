#ifndef MY_VEC_H
#define MY_VEC_H
#include <cstdio>
#include <iostream>

#include "debug_new.h"

//#define DEBUG
#include "debug_info.h"

template <typename T>
class Vector {
    T* buf;
    size_t sz;
    size_t cp;

    size_t number_obj = 0;

    void destroy ();
    void reallocate ();

public:
    Vector () : buf (nullptr), sz (0), cp (0) { 
        //count++, number_obj = count;
        //printf ("Default Constructor num = %lu\n", number_obj);
    }

    explicit Vector (size_t n, const T& value = T ());

    Vector (const Vector<T>& other);

    Vector (Vector<T>&& other);


    template <typename... Args>
    void emplase_back (Args&&...  args) {
        //printf ("emplase_back ()!\n");
        DEB_INFO
        if (sz == cp) {
            reallocate ();
        }
        DEB_INFO
        new (static_cast<void*> (buf + sz)) T (std::forward<Args>(args)...);
        sz++;
    }

    void push_back (T&& value);

    void push_back (const T& value);

    void print ();


    Vector& operator= (const Vector& other) = delete;

    ~Vector ();
    
    size_t size () const;

    size_t capcity () const;

    T& operator[] (size_t i);
    const T& operator[] (size_t i) const;

    size_t max_element () const;

};


template <typename T>
void Vector<T>::print () {
    for (size_t i = 0; i < sz; ++i)
        std::cout << buf[i] << " ";
    printf ("\n");
}


template <typename T>
void Vector<T>::destroy () {
    // printf ("Destroy! %lu\n", number_obj); 
    for (size_t i = 0; i < sz; ++i) {
        (buf + i)->~T();
    }
    delete[] reinterpret_cast<char*> (buf);
}

template <typename T>
void Vector<T>::reallocate () {
    // printf ("reallocate\n");
    T* buf_new = reinterpret_cast<T*> (NEW char [sz == 0 ? sizeof (T) : 2 * sz * sizeof (T)]);
    cp = (sz == 0 ? 1 : sz * 2);

    for (size_t i = 0; i < sz; ++i) {
        new (buf_new + i) T (std::move (buf[i]));
    }
    destroy ();
    buf = buf_new;
}

template <typename T>
Vector<T>::Vector (size_t n, const T& value) : sz (n), cp (n){
        
    //count++, number_obj = count;
    // printf ("Constructor num = %lu!\n", number_obj);

    buf = reinterpret_cast<T*> (NEW char [n * sizeof (T)]);
    
    for (size_t i = 0; i < n; ++i) {
        new (static_cast<void*> (buf + i)) T (value);
    }
}

template <typename T>
Vector<T>::Vector (const Vector<T>& other) : sz (other.sz), cp (other.cp) {

    //count++, number_obj = count;
    // printf ("Copy Constructor obj_num = %lu!\n", number_obj);
    buf = reinterpret_cast<T*> (NEW char [sz * sizeof (T)]);
    for (size_t i = 0; i < sz; ++i) {
        new (static_cast<void*> (buf + i)) T (std::move (other.buf[i]));
    }

}

template <typename T>
Vector<T>::Vector (Vector<T>&& other) : sz (other.sz), cp (other.cp) {
    number_obj = other.number_obj;
    // printf ("Move constructor!\n");
    buf = other.buf;
    other.buf = nullptr;
}



template <typename T>
void Vector<T>::push_back (T&& value) {
    DEB_INFO
    emplase_back (std::move (value));
    DEB_INFO
}

template <typename T>
void Vector<T>::push_back (const T& value) {
    if (sz == cp) {
        reallocate ();
    }
    new (static_cast<void*> (buf + sz)) T (value);
    sz++;
}

template <typename T>
Vector<T>::~Vector () {
    destroy ();
}

template <typename T>
size_t Vector<T>::size () const {
    return sz;
}

template <typename T>
size_t Vector<T>::capcity () const {
    return cp;
}

template <typename T>
T& Vector<T>::operator[] (size_t i)  {
    return buf[i];
}

template <typename T>
const T& Vector<T>::operator[] (size_t i) const {
    return buf[i];
}

template <typename T>
size_t Vector<T>::max_element () const {
    T max_elem = buf[0];
    size_t index = 0;
    for (size_t i = 1; i < sz; ++i) {
        if (buf[i] > max_elem) {
            max_elem = buf[i];
            index = i;
        }
    }

    return index;
}








#endif //NY_VEC_H