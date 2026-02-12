#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdint.h>
#include <stdbool.h>

#define MIN_PORT_ALLOWED 1024

bool is_port_valid(uint16_t port);
bool is_port_available(uint16_t port);
bool sock_failure(int res);
bool thread_failure(int res);

#endif // VALIDATION_H