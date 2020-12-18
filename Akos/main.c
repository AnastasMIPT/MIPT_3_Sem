#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* thread_func(void* arg)
{
    pthread_mutex_t* mutex = arg;

    int val = 0;
    size_t part_res = 0;
    pthread_mutex_lock (mutex);
    while (scanf("%d", &val) > 0) {
        part_res += val;
    }
    pthread_mutex_unlock (mutex);
    return (void*)part_res;
}

int main(int argc, char** argv)
{
    int k = atoi(argv[1]);

    pthread_t threads[k];
    int part_sum[k];
    memset(part_sum, 0, sizeof(part_sum));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    size_t res = 0;

    for (int i = 0; i < k; ++i) {
        pthread_create(&threads[i], NULL, thread_func, &mutex);
    }

    size_t part_res = 0;
    for (int i = 0; i < k; ++i) {
        pthread_join(threads[i], (void*) &part_res);
        res += part_res;
    }

    printf("%lu\n", res);

    pthread_attr_destroy(&attr);

    return 0;
}