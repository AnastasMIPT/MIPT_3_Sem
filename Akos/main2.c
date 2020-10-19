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
    if (EOF == scanf("%s", buf)) {
        printf("0\n");
        exit(0);
    }
    pid_t pid = fork();
    if (-1 == pid) {
        perror("fork:");
        exit(0);
    }

    if (0 == pid) {
        while (scanf("%s", buf) != EOF) {

            pid_t pid2 = fork();
            if (-1 == pid2) {
                perror("fork:");
                exit(0);
            }

            if (0 != pid2) {
                int status = 0;
                waitpid(pid2, &status, 0);
                exit(WEXITSTATUS(status) + 1);
            }
        }
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        printf("%d\n", WEXITSTATUS(status) + 1);
    }
    exit(0);
}