#include <arpa/inet.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

volatile sig_atomic_t term = 0;

void sig_handler()
{
    term = 1;
}

void set_signals()
{
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));

    act.sa_handler = sig_handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
}

int main(int argc, char** argv)
{
    // Converts address from IPv4 numbers-and-dots notation into binary data
    // in network byte order.
    const in_addr_t ipv4 = inet_addr("127.0.0.1");
    // Convert port from string into 16-bit network byte order.
    const in_port_t port = htons(strtol(argv[1], NULL, 10));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = ipv4;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("unable to create sockfd");
        return 1;
    }
    // Set connection.
    if (connect(sockfd, (const struct sockaddr *)&addr,
            sizeof(struct sockaddr_in)) == -1) {
        perror("connection refused");
        close(sockfd);
        return 1;
    }

    const size_t BUFFER_SIZE = 10000;
    char filename[PATH_MAX];
    char query[PATH_MAX];
    char buffer[BUFFER_SIZE];

    memset(filename, 0, PATH_MAX);
    memset(query, 0, PATH_MAX);
    memset(buffer, 0, BUFFER_SIZE);

    printf("Enter file name: ");
    scanf("%s", filename);

    strcat(query, "GET ");
    strcat(query, filename);
    strcat(query, " HTTP/1.1\n");

    printf("Send: %s\n", query);
    write(sockfd, query, PATH_MAX);

    char* cur_pos = buffer;
    int read_count = 0;
    int left_read = BUFFER_SIZE;
    while ((read_count = read(sockfd, cur_pos, left_read)) > 0) {
        cur_pos += read_count;
        left_read -= read_count;
    }
    printf("%s", buffer);

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
    return 0;
}
