#ifndef SEVER_H
#define SERVER_H

#include <stdint.h>

#define MAX_CONCURRENT_CLIENTS 10
#define MAX_PAYLOAD_SIZE 8192

void start(uint16_t port);
void *handle_client(void *client_ptr);

#endif // SERVER_H