#include "http_server.h"
#include <stdio.h>      
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h>  
#include <unistd.h> 
#include <arpa/inet.h>
#include <stdlib.h>  
#include <pthread.h>
#include <string.h>
#include "validation.h"
#include "log.h"
#include "http_request.h"
#include "http_response.h"
#include "http_parser.h"
#include "http_handler.h"

/**
 * Initializes a sockaddr_in structure with the given port.
 * Sets up the address to bind to any available interface (INADDR_ANY).
 * 
 * @param server_addr Pointer to the sockaddr_in structure to initialize
 * @param port The port number to bind to (in host byte order)
 */
static void init_server_addr(struct sockaddr_in *server_addr, uint16_t port) {
    memset(server_addr, 0, sizeof(*server_addr));
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(port);
}

/**
 * Thread function to handle an individual client connection.
 * Reads the HTTP request, parses it, generates a response, and sends it back.
 * Automatically cleans up resources and closes the connection when done.
 * 
 * @param client_ptr Pointer to an int containing the client socket file descriptor
 *                   This memory is freed by the function
 * @return Always returns NULL (pthread requirement)
 */
void *handle_client(void *client_ptr) {
    int client_fd = *(int *)client_ptr;
    free(client_ptr);

    char buffer[MAX_PAYLOAD_SIZE];
    size_t total_read = 0;
    ssize_t n;

    while (total_read < MAX_PAYLOAD_SIZE - 1) {
        n = read(client_fd, buffer + total_read, MAX_PAYLOAD_SIZE - 1 - total_read);
        if (n <= 0) break; // client closed or error
        total_read += n;
        buffer[total_read] = '\0';
        if (strstr(buffer, "\r\n\r\n")) break; // end of headers
    }

    http_request_t request = parse_http_request(buffer, total_read);
    http_response_t response = handle_request(&request);
    
    const char *status_msg;
    switch (response.status_code) {
        case OK:
            status_msg = STATUS_OK_MSG;
            break;
        case BAD_REQUEST:
            status_msg = STATUS_BAD_REQUEST_MSG;
            break;
        case NOT_FOUND:
            status_msg = STATUS_NOT_FOUND_MSG;
            break;
        default:
            status_msg = "Unknown";
            break;
    }
    
    const char *content_type_str = (response.content_type == TEXT_HTML) ? "text/html" : "text/plain";
    
    char header[1024];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Length: %zu\r\n"
        "Content-Type: %s\r\n"
        "Connection: close\r\n"
        "\r\n",
        response.status_code,
        status_msg,
        response.content_length,
        content_type_str
    );

    size_t written = 0;
    while (written < (size_t)header_len) {
        ssize_t w = write(client_fd, header + written, header_len - written);
        if (w <= 0) break;
        written += w;
    }

    if (response.body && response.content_length > 0) {
        written = 0;
        while (written < response.content_length) {
            ssize_t w = write(client_fd, response.body + written, response.content_length - written);
            if (w <= 0) break;
            written += w;
        }
        free(response.body);
    }

    free_http_request(&request);
    close(client_fd);
    return NULL;
}

/**
 * Starts the HTTP server on the specified port.
 * Creates a listening socket and enters an infinite loop accepting connections.
 * Each client connection is handled in a separate detached thread.
 * 
 * @param port The port number to listen on (must be >= 1024)
 */
void start(uint16_t port) {
    log_write(LOG_INFO, "Starting TCP Server on port %u", port);

    if (!is_port_valid(port)) {
        log_write(LOG_ERROR, "Given port %u is not valid.", port);
        return;
    }

    if (!is_port_available(port)) {
        log_write(LOG_ERROR, "Given port %u is not available. Check if any process is using that port.", port);
        return;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_failure(server_fd)) {
        log_write(LOG_ERROR, "Error while initializing server file descriptor");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    init_server_addr(&server_addr, port);

    int bind_res = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (sock_failure(bind_res)) {
        log_write(LOG_ERROR, "Error while binding");
        close(server_fd);
        return;
    }

    int listen_res = listen(server_fd, SOMAXCONN);
    if (sock_failure(listen_res)) {
        log_write(LOG_ERROR, "Error while listening");
        close(server_fd);
        return;
    }

    while (1) {
        int *client_fd = malloc(sizeof(int));
        if (!client_fd) {
            log_write(LOG_WARN, "Could not allocate client file descriptor");
            continue;
        }

        *client_fd = accept(server_fd, NULL, NULL);
        if (sock_failure(*client_fd)) {
            log_write(LOG_ERROR, "Error while accepting incoming connection");
            free(client_fd);
            continue;
        }

        pthread_t thread;
        int thread_res = pthread_create(&thread, NULL, handle_client, client_fd);
        if (thread_failure(thread_res)) {
            log_write(LOG_ERROR, "Error while creating thread");
            close(*client_fd);
            free(client_fd);
            continue;
        }

        pthread_detach(thread);
    }
}