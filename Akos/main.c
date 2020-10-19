#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char buf[BUFSIZ];
    pid_t pid = 0;
    int status = 0;
    
    while (scanf("%s", buf) != EOF) {
        
        if (pid == 0) {
            pid = fork();
        }
        if (-1 == pid) {
            perror ("fork:");
            exit (0);
        }

        if (0 != pid) {
            waitpid (pid, &status, 0);
        }

    } 
    printf ("%d\n", status);
    exit(0);
    
    
}