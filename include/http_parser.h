#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "http_request.h"
#include <stdlib.h>

#define MAX_REQUEST_LINE 1024

http_request_t parse_http_request(const char *buffer, size_t length);

#endif // HTTP_PARSER_H
