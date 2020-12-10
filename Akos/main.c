#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t signal_is = 0;

void sig_handler(int sign)
{
    signal_is = 1;
}

int StartListenngTCP(const char* IPv4, const char* port);
void SetSignalHandlers();
void ProccesConnection(int client_fd);
void SetEventInfo(int cur_fd, int epoll_fd);
void HandleNewConnections(int tcp_socket, int epoll_fd);

int main(int argc, char** argv)
{

    SetSignalHandlers();

    int tcp_socket = StartListenngTCP("127.0.0.1", argv[1]);
    fcntl(
        tcp_socket,
        F_SETFL,
        fcntl(tcp_socket, F_GETFL) |
            O_NONBLOCK); // now accept() doesn't block program

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }
    SetEventInfo(tcp_socket, epoll_fd);

    struct epoll_event event_buf[BUFSIZ];

    while (!signal_is) {
        int event_count = epoll_wait(epoll_fd, event_buf, BUFSIZ, -1);
        if (-1 == event_count) {
            break;
        }
        for (int i = 0; i < event_count; ++i) {
            int cur_fd = event_buf[i].data.fd;
            if (cur_fd == tcp_socket) {
                HandleNewConnections(tcp_socket, epoll_fd);
            } else {
                ProccesConnection(cur_fd);
            }
        }
    }

    close(epoll_fd);
    close(tcp_socket);
    return 0;
}

void ProccesConnection(int client_fd)
{
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);

    int n_read = read(client_fd, buf, BUFSIZ);
    if (-1 == n_read || 0 == n_read) {
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
        return;
    }

    for (int i = 0; i < n_read; ++i) {
        buf[i] = toupper(buf[i]);
    }

    int n_write = write(client_fd, buf, n_read);
    if (-1 == n_write || 0 == n_write) {
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
        return;
    }
}

void HandleNewConnections(int tcp_socket, int epoll_fd)
{
    int client_fd = 0;
    while (1) {
        client_fd = accept(tcp_socket, NULL, NULL);
        fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL) | O_NONBLOCK);
        if (-1 == client_fd)
            break;
        SetEventInfo(client_fd, epoll_fd);
    }
}

void SetEventInfo(int cur_fd, int epoll_fd)
{
    struct epoll_event poll_ev = {.events = EPOLLIN, .data.fd = cur_fd};
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cur_fd, &poll_ev);
}

void SetSignalHandlers()
{
    struct sigaction sa = {.sa_handler = sig_handler, .sa_flags = SA_RESTART};
    sigaction(SIGTERM, &sa, NULL);
}

int StartListenngTCP(const char* IPv4, const char* port)
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == tcp_socket) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(IPv4);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));

    if (-1 == bind(tcp_socket, (const struct sockaddr*)&addr, sizeof(addr))) {
        perror("bind");
        close(tcp_socket);
        return -1;
    }

    if (-1 == listen(tcp_socket, SOMAXCONN)) {
        perror("listen");
        close(tcp_socket);
        return -1;
    }
    return tcp_socket;
}