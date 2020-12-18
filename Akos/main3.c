
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* sum(void* arg)
{
    int* part_sum = (int*)arg;
    int num = 0;
    while (scanf("%d", &num) > 0) {
        *part_sum += num;
    }
    return NULL;
}


int main(int argc, char** argv)
{
    size_t N = strtol(argv[1], NULL, 10);

    pthread_t threads[N];
    int part_sums[N];
    memset(part_sums, 0, N*sizeof(int));

    // Create threads' attribute.
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Minimize memory usage.
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);

    for (size_t i = 0; i < N; ++i) {
        if (pthread_create(&threads[i], NULL, sum, &part_sums[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    int result = 0;
    for (size_t i = 0; i < N; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
        result += part_sums[i];
    }

    printf("%d\n", result);
    // Destroy threads' attribute.
    if (pthread_attr_destroy(&attr) != 0) {
        perror("pthread_attr_destroy");
        exit(EXIT_FAILURE);
    }

    return 0;
}
