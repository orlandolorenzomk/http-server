/**
 * @file validation.h
 * @brief Port and socket validation utilities
 * 
 * Provides functions to validate ports and check for errors in
 * socket and thread operations.
 */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdint.h>
#include <stdbool.h>

/** Minimum port number allowed (ports below 1024 require root) */
#define MIN_PORT_ALLOWED 1024

/**
 * Checks if a port number is valid for server use.
 * 
 * @param port The port number to validate
 * @return true if port >= 1024, false otherwise
 */
bool is_port_valid(uint16_t port);

/**
 * Checks if a port is available for binding.
 * 
 * @param port The port number to check
 * @return true if the port is available, false if in use or on error
 */
bool is_port_available(uint16_t port);

/**
 * Checks if a socket operation failed.
 * 
 * @param res The result code from a socket operation
 * @return true if the operation failed (res < 0), false otherwise
 */
bool sock_failure(int res);

/**
 * Checks if a pthread operation failed.
 * 
 * @param res The result code from a pthread operation
 * @return true if the operation failed (res != 0), false otherwise
 */
bool thread_failure(int res);

#endif // VALIDATION_H