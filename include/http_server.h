#ifndef HTTP_SEVER_H
#define HTTP_SERVER_H

#include <stdint.h>

#define MAX_CONCURRENT_CLIENTS 10
#define MAX_PAYLOAD_SIZE 8192

void start(uint16_t port);
void *handle_client(void *client_ptr);

#endif // HTTP_SERVER_H