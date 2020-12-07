
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

struct event_info {
    int fd;
    char ended;
};

size_t read_data(int epoll_fd, int N, int in[N])
{
    struct epoll_event event_buf[BUFSIZ];
    char read_buf[BUFSIZ];
    size_t result = 0;

    int open_fd_count = N;
    while (open_fd_count) {
        int event_count = epoll_wait(epoll_fd, event_buf, BUFSIZ, -1);
        for (int i = 0; i < event_count; ++i) {
            int cur_fd = ((struct event_info*)event_buf[i].data.ptr)->fd;
            int n_read = read(cur_fd, read_buf, BUFSIZ);
            if (n_read > 0) {
                result += n_read;
            } else {
                close(cur_fd);
                open_fd_count--;
            }
        }
    }
    close(epoll_fd);
    return result;
}

extern size_t read_data_and_count(size_t N, int in[N])
{
    for (size_t i = 0; i < N; ++i) {
        fcntl(in[i], F_SETFL, fcntl(in[i], F_GETFL) | O_NONBLOCK);
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }

    struct event_info* events_info = calloc(N, sizeof(struct event_info));
    for (int i = 0; i < N; ++i) {
        events_info[i].fd = in[i];
        events_info[i].ended = 0;
    }

    for (size_t i = 0; i < N; ++i) {
        struct epoll_event poll_ev = {
            .events = EPOLLIN, .data.ptr = &events_info[i]};
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, in[i], &poll_ev);
    }

    return read_data(epoll_fd, N, in);
}
