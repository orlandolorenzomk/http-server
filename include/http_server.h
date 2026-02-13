/**
 * @file http_server.h
 * @brief Core HTTP server functionality
 * 
 * Provides the main server loop, socket handling, and multi-threaded
 * client connection management.
 */

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdint.h>

/** Maximum size of HTTP request payload in bytes */
#define MAX_PAYLOAD_SIZE 8192

/**
 * Starts the HTTP server on the specified port.
 * Creates a listening socket and enters an infinite loop accepting connections.
 * 
 * @param port The port number to listen on (must be >= 1024)
 */
void start(uint16_t port);

/**
 * Thread function to handle an individual client connection.
 * 
 * @param client_ptr Pointer to an int containing the client socket file descriptor
 * @return Always returns NULL (pthread requirement)
 */
void *handle_client(void *client_ptr);

#endif // HTTP_SERVER_H