#include "http_handler.h"
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

/**
 * Handles an HTTP request and generates an appropriate response.
 * Routes requests based on method and path.
 * Currently supports GET / with a simple "Hello, world!" response.
 * 
 * @param request Pointer to the parsed HTTP request
 * @return An http_response_t structure containing status, headers, and body
 *         The caller is responsible for freeing response.body if non-NULL
 */
http_response_t handle_request(http_request_t *request) {
    http_response_t response;

    response.content_type = TEXT_PLAIN;
    response.body = NULL;
    response.content_length = 0;

    if (request->parse_status != PARSE_OK) {
        response.status_code = BAD_REQUEST;
        const char *msg = STATUS_BAD_REQUEST_MSG;
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) {
            strcpy(response.body, msg);
        }
        return response;
    }

    if (request->method == GET && strcmp(request->target_path, "/") == 0) {
        response.status_code = OK;
        const char *msg = "Hello, world!";
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) {
            strcpy(response.body, msg);
        }
    } else {
        response.status_code = NOT_FOUND;
        const char *msg = STATUS_NOT_FOUND_MSG;
        response.content_length = strlen(msg);
        response.body = malloc(response.content_length + 1);
        if (response.body) {
            strcpy(response.body, msg);
        }
    }

    return response;
}