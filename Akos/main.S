.intel_syntax noprefix

    .text
    #include <sys/syscall.h>
    .global _start
 

_start:

    mov rcx, 1
    
.loop:
    cmp rcx, 0
    je .end_loop

    mov rax, SYS_read
    mov rdi, STDIN
    mov rsi, buf_ptr
    mov rdx, len_of_buf
    syscall


    mov r8, rax

    

    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, buf_ptr
    mov rdx, r8
    syscall

    cmp r8, len_of_buf
    jae .loop 


 .end_loop:

    mov rax, SYS_exit
    mov rdi, 0
    syscall



.data


len_of_buf: .quad 907
.lcomm buf, 907
buf_ptr: .quad buf

    

STDOUT:    .quad 1
STDIN:     .quad 0
