#include <sys/syscall.h>

enum {
    stdout = 1
};

long syscall(long number, ...);

void _start () {
    const char Message[] = "Hello, World!";
    syscall (SYS_write, stdout, Message, sizeof (Message) - 1);
    syscall (SYS_exit , 0);
}