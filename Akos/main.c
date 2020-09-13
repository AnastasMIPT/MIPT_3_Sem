//#include <unistd.h>
//#include <sys/syscall.h>

#define SizeOfBuf  997
#define SYS_write 1
#define SYS_read  0
#define SYS_exit 60
#define stdout 1
#define stdin 0

long syscall(long number, ...);

void _start () {
    char Message[SizeOfBuf] = {};
    long num_symbls = -1;
    while (num_symbls != 0) {
        num_symbls = syscall (SYS_read, stdin, Message, SizeOfBuf);
        syscall (SYS_write, stdout, Message, num_symbls);
        if (num_symbls < SizeOfBuf) break;
    }
    
    syscall (SYS_exit , 0);
}