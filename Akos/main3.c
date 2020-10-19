#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    int num = 0;
    int pid = 0;
    do {
        num++;
        pid = fork();
    } while (pid == 0);

    if (pid == -1)
        printf("%d\n", num);

    exit(0);
}