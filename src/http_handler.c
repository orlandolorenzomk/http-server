#include "http_handler.h"
#include <stdlib.h>
#include <string.h>

http_response_t handle_request(http_request_t *request) {
    http_response_t response;

    response.content_type = TEXT_PLAIN;
    response.body = NULL;
    response.content_length = 0;

    if (request->parse_status != PARSE_OK) {
        response.status_code = BAD_REQUEST;
        const char *msg = BAD_REQUEST_MSG;
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) strcpy(response.body, msg);
        return response;
    }

    if (request->method == GET && strcmp(request->target_path, "/") == 0) {
        response.status_code = OK;
        const char *msg = "Hello, world!";
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) strcpy(response.body, msg);
    } else {
        response.status_code = NOT_FOUND;
        const char *msg = BAD_REQUEST_MSG;
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) strcpy(response.body, msg);
    }

    return response;
}