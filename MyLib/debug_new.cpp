#ifndef DEBUG_NEW_H
#define DEBUG_NEW_H


#include <cstdio>
#include <cstdlib>


FILE* Log = nullptr;

#define DEBUG_NEW

void* operator new (size_t size, const char* file, const char* func, int line, FILE* f_log) {
    void* ptr = malloc (size);

    if (f_log == nullptr) f_log = stdout;
    fprintf (f_log, "%p Вызван оператор new из | FILE: %s | FUNC: %s | LINE: %d |" 
            "Запрашиваемый размер: %lu байт\n", ptr, file, func, line, size);
    return ptr;
}

void* operator new[] (size_t size, const char* file, const char* func, int line, FILE* f_log) {
    void* ptr = malloc (size);

    if (f_log == nullptr) f_log = stdout;
    fprintf (f_log, "%p Вызван оператор new[] из | FILE: %s | FUNC: %s | LINE: %d |" 
            "Запрашиваемый размер: %lu байт\n", ptr, file, func, line, size);
    return ptr;
}




#ifdef DEBUG_NEW
#define new new (__FILE__, __PRETTY_FUNCTION__, __LINE__, Log)
#endif

struct A {
    int first;
    int second;
    A () = default;
    A (int val) {
        first = second = val;
    }
    ~A () {
        //printf ("Distructor\n");
    }
};

int main () {

    //Log = fopen ("logs.txt", "w");

    A* a = new A;
    //printf ("%s\n", __PRETTY_FUNCTION__);

    delete a;

    //fclose (Log);
    return 0;
}

#endif  // DEBUG_NEW_H