#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>


extern void* my_malloc (size_t size);
extern void my_free (void* ptr);
extern void myalloc_initialize (int fd /* открытый на R/W файловый дескриптор существующего файла */);
extern void myalloc_finalize ();


typedef int64_t Align;

union header {                 // header является объединением, чтобы выровнять по sizeof (Align)
    struct {
        union header* next;
        uint32_t size;
    } b;
    Align align_member;
};





typedef union header Header;
static Header* head;             // начальный пустой список
static Header* free_p = NULL;   // указатель на свободный блок (изначально - первый) 
static off_t mem_size;

int error = 0;

void myalloc_initialize (int fd) {

    struct stat stats;
    if (-1 == fstat (fd, &stats)) {
        error = 1;
        return;
    }
    mem_size = stats.st_size;
    
    if (mem_size < sizeof (Header)) {
        error = 1;
        return;
    }

    head = mmap (NULL, mem_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (MAP_FAILED == head) {
        error = 1;
        return;
    }

    head->b.next = head;
    head->b.size = (mem_size - sizeof (Header)) / sizeof (Header);
    free_p = head;

}

void myalloc_finalize () {
    if (error) return;
    munmap (head, mem_size);
}

void* my_malloc (size_t size) {
    if (error) return NULL;

    Header* prev_p = free_p;
    uint32_t num_units = (size + sizeof (Header) - 1) / sizeof (Header) + 1;
    
    Header* ptr = NULL;
    Header* prev_ptr = NULL;
    for (Header* p = prev_p->b.next; p != NULL; prev_p = p, p = ptr->b.next) {
        if (p->b.size >= num_units) {
            if (ptr == NULL || p->b.size < ptr->b.size) {
                prev_ptr = prev_p;
                ptr = p;
            }
        }
        if (p == free_p) break;
    }
    if (ptr == NULL) return NULL;

    if (ptr->b.size == num_units) {
        prev_ptr->b.next = ptr->b.next;
    } else {
        ptr->b.size -= num_units;
        ptr += ptr->b.size;
        ptr->b.size = num_units;
    }
    free_p = prev_ptr;
    return (void*) (ptr + 1);
}

void my_free (void* ptr) {
    if (error) return;

    Header *ptr_hdr, *p;
    ptr_hdr = (Header*) ptr - 1; // указатель на заголовок

    for (p = free_p; ptr_hdr <= p || ptr_hdr >= p->b.next; p = p->b.next)
        if (p >= p->b.next && (ptr_hdr > p || ptr_hdr < p->b.next))
            break; /* освобождаемый блок в начале или в конце */

    if (ptr_hdr + ptr_hdr->b.size == p->b.next) { //сливаем со следующим
        ptr_hdr->b.size += p->b.next->b.size;
        ptr_hdr->b.next = p->b.next->b.next;
    } else
        ptr_hdr->b.next = p->b.next;
    if (p + p->b.size == ptr_hdr) {  //сливаем с предыдущим
        p->b.size += ptr_hdr->b.size;
        p->b.next = ptr_hdr->b.next;
    } else
        p->b.next = ptr_hdr;
    free_p = p;
}