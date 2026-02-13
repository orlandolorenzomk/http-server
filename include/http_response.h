#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdlib.h>

typedef enum {
    OK = 200,
    NOT_FOUND = 404,
    BAD_REQUEST = 400
} http_status_code_t;

typedef enum {
    TEXT_PLAIN,
    TEXT_HTML
} http_content_type_t;

typedef struct {
    http_status_code_t status_code;
    size_t content_length;
    http_content_type_t content_type;
    char *body;
} http_response_t;

#endif // HTTP_RESPONSE_H