#include "validation.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

bool is_port_valid(uint16_t port) {
    return port >= MIN_PORT_ALLOWED;
}

bool is_port_available(uint16_t port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return false;

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bool available = (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0);
    close(sock);
    return available;
}

bool sock_failure(int res) {
    return res < 0;
}

bool thread_failure(int res) {
    return res != 0;
}