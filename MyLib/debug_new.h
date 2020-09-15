#ifndef DEBUG_NEW_H
#define DEBUG_NEW_H


#include <cstdio>
#include <cstdlib>


extern FILE* Log; // файл для записи логов

//#define DEBUG_NEW



/*!! С помощью этого заголовочника можно перехватить оператор new, чтобы вывести дополнительную
информацию в Log файл. В исходной программе необходимо писать "NEW" вместо new, и перед включением этого
заголовочника написать #define DEBUG_NEW. Если не написать define, то NEW заменится на обычный new.
*/

#ifdef DEBUG_NEW

#define NEW new (__FILE__, __PRETTY_FUNCTION__, __LINE__, Log)

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

void operator delete (void* ptr) noexcept
{
    if (ptr) {
        if (Log == nullptr) Log = stdout;
        fprintf (Log, "%p Вызван оператор delete\n" , ptr);
        free (ptr);
    }
}

void operator delete[] (void* ptr) noexcept
{
    if (ptr) {
        if (Log == nullptr) Log = stdout;
        fprintf (Log, "%p Вызван оператор delete[]\n" , ptr);
        free (ptr);
    }
}
#else
#define NEW new

#endif


#endif  // DEBUG_NEW_H