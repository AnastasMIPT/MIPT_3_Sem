#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <zconf.h>

volatile sig_atomic_t signal_is = 0;
int wait_connection = 0;

void sig_handler(int sign)
{
    signal_is = 1;
    if (wait_connection) {
        exit(0);
    }
}

void SetSignalHandlers();
int StartListenngTCP(const char* IPv4, const char* port);
void ProccesConnection(int client_fd, char* path);
void ProccesReadbleFile(int client_fd, const char* path_to_file);

int main(int argc, char** argv)
{
    int tcp_socket = StartListenngTCP("127.0.0.1", argv[1]);
    SetSignalHandlers();

    while (!signal_is) {
        wait_connection = 1;
        int client_fd = accept(tcp_socket, NULL, NULL);
        if (-1 == client_fd) {
            break;
        }
        wait_connection = 0;
        //printf("accepted fd = %d\n", client_fd);

        ProccesConnection(client_fd, argv[2]);

        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }

    close(tcp_socket);
    return 0;
}

void ProccesConnection(int client_fd, char* path)
{
    char path_to_file[PATH_MAX];
    memset(path_to_file, 0, PATH_MAX);
    strncpy(path_to_file, path, PATH_MAX);

    char buf[BUFSIZ];
    if (-1 == read(client_fd, buf, BUFSIZ)) {
        perror("read");
        return;
    }

    sscanf(buf, "GET %s", buf);
    strcat(path_to_file, "/");
    strcat(path_to_file, buf);

    if (-1 == access(path_to_file, F_OK)) {
        dprintf(client_fd, "HTTP/1.1 404 Not Found\r\n");
    } else if (-1 == access(path_to_file, R_OK)) {
        dprintf(client_fd, "HTTP/1.1 403 Forbidden\r\n");
    } else if (-1 != access(path_to_file, X_OK)) {
        dprintf(client_fd, "HTTP/1.1 200 OK\r\n");
        pid_t pid = fork();
        if (-1 == pid) {
            perror("fork");
            return;
        }
        if (0 == pid) {
            if (-1 == dup2(client_fd, 1)) {
                perror("dup2");
            }
            close(client_fd);
            execl(path_to_file, path_to_file, NULL);
            perror("execl");
        }
        wait(0);
    } else {
        ProccesReadbleFile(client_fd, path_to_file);
    }
}

void ProccesReadbleFile(int client_fd, const char* path_to_file)
{

    struct stat f_stats;
    stat(path_to_file, &f_stats);
    dprintf(
        client_fd,
        "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n",
        f_stats.st_size);
    int fd = open(path_to_file, O_RDONLY);
    char buf[BUFSIZ];
    int nread = 0;
    while ((nread = read(fd, buf, BUFSIZ)) > 0) {
        write(client_fd, buf, nread);
    }

    close(fd);
}

void SetSignalHandlers()
{

    struct sigaction sa = {.sa_handler = sig_handler, .sa_flags = SA_RESTART};
    sigaction(SIGINT, &sa, NULL);
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