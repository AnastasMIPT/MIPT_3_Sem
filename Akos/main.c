enum {
    SizeOfBuf = 997,
    SYS_write = 1,
    SYS_read  = 0,
    SYS_exit  = 60,
    stdout    = 1,
    stdin     = 0
};



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