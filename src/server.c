#include "server.h"
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

static void init_server_addr(struct sockaddr_in *server_addr, uint16_t port) {
    memset(server_addr, 0, sizeof(*server_addr));
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(port);
}

void *handle_client(void *client_ptr) {
    int client_fd = *(int *)client_ptr;
    free(client_ptr);

    char buffer[MAX_PAYLOAD_SIZE];
    ssize_t n;

    while ((n = read(client_fd, buffer, MAX_PAYLOAD_SIZE - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s\n", buffer);
        fflush(stdout);
    }

    close(client_fd);
    return NULL;
}

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
            log_write(LOG_ERROR, "Error while accepting incominig connection");
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