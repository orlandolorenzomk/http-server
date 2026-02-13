#include "validation.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

/**
 * Checks if a port number is valid for server use.
 * Ports below 1024 are reserved and require elevated privileges.
 * 
 * @param port The port number to validate
 * @return true if port >= 1024, false otherwise
 */
bool is_port_valid(uint16_t port) {
    return port >= MIN_PORT_ALLOWED;
}

/**
 * Checks if a port is available for binding.
 * Attempts to create a socket and bind to the port.
 * 
 * @param port The port number to check
 * @return true if the port is available, false if in use or on error
 */
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

/**
 * Checks if a socket operation failed.
 * 
 * @param res The result code from a socket operation
 * @return true if the operation failed (res < 0), false otherwise
 */
bool sock_failure(int res) {
    return res < 0;
}

/**
 * Checks if a pthread operation failed.
 * 
 * @param res The result code from a pthread operation
 * @return true if the operation failed (res != 0), false otherwise
 */
bool thread_failure(int res) {
    return res != 0;
}