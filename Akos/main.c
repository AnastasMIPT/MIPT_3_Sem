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

const int MaxFormatLen = 20;


void print_num (char* memory, const char* format, int N, int W, char* position, int val);

int main (int argc, char** argv) {
    char* f_in_name = argv[1];
    int N = 0;
    int W = 0;
    char format[MaxFormatLen];
    sscanf (argv[2], "%d", &N);
    sscanf (argv[3], "%d", &W);
    sprintf (format, "%%%sd", argv[3]);


    int fd = open (f_in_name, O_RDWR | O_CREAT | O_TRUNC, 0640);
    if (fd == -1) return 0;

    int64_t f_size = N * (N * W + 1);
    
    if (-1 == ftruncate (fd, f_size)) return 0;


    char* memory = mmap (NULL, f_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == memory) return 0;

    close (fd);


    int num = 1;
    char buf_symb = 0;
    char* position = 0;
    for (int i = 0; i < N / 2 + N % 2; ++i) {
        int len = N - 2 * i;
        for (int j = i; j < N - i; ++j) {
            
            print_num (memory, format, N, W,
                       memory + (i * N + j) * W + i, num + j);
            print_num (memory, format, N, W, 
                       memory + (j * N + N - 1 - i) * W + j, num +     (len - 1) + j);
            print_num (memory, format, N, W,
                       memory + ((N - 1 - i) * N + N - j - 1) * W + (N - 1 - i), num + 2 * (len - 1) + j);
            print_num (memory, format, N, W, 
                       memory + ((N - j - 1) * N + i) * W + (N - j - 1), num + 3 * (len - 1) + j);

        }
        print_num (memory, format, N, W,
                   memory + (i * N + i) * W + i, num + i);

        num += 4 * (len - 1) - 1;
   
    }
    for (int i = 0; i < N; ++i) {
        *(memory + (i * N + N) * W + i) = '\n';
    }

    munmap (memory, f_size);

}

void print_num (char* memory, const char* format, int N, int W, char* position, int val) {
    char buf_symb = *(position + W);
    sprintf (position, format, val);
    *(position + W) = buf_symb;
}