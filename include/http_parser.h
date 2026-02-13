#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "http_request.h"
#include <stdlib.h>

#define MAX_REQUEST_LINE 1024

#define EOR "\r\n"

#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_PUT "PUT"
#define METHOD_DELETE "DELETE"

#define VERSION_HTTP_0_9 "HTTP/0.9"
#define VERSION_HTTP_1_0 "HTTP/1.0"
#define VERSION_HTTP_1_1 "HTTP/1.1"
#define VERSION_HTTP_2   "HTTP/2"
#define VERSION_HTTP_3   "HTTP/3"

http_request_t parse_http_request(const char *buffer, size_t length);

#endif // HTTP_PARSER_H
