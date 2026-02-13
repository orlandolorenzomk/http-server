#include "http_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Parses an HTTP request from a buffer.
 * Extracts the method, target path, and HTTP version from the request line.
 * 
 * @param buffer The buffer containing the raw HTTP request
 * @param length The length of the buffer
 * @return An http_request_t structure with parsed data and parse status
 *         The target_path field is dynamically allocated and must be freed
 */
http_request_t parse_http_request(const char *buffer, size_t length) {
    http_request_t request;
    request.method = GET; // default
    request.version = HTTP_1_1;
    request.target_path = NULL;
    request.parse_status = PARSE_BAD_REQUEST;

    const char *end_of_line = strstr(buffer, EOR);
    if (!end_of_line || (size_t)(end_of_line - buffer) > MAX_REQUEST_LINE) {
        request.parse_status = PARSE_TOO_LARGE;
        return request;
    }

    size_t line_len = end_of_line - buffer;
    if (line_len >= length) {
        request.parse_status = PARSE_BAD_REQUEST;
        return request;
    }
    
    char *line = malloc(line_len + 1);
    if (!line) {
        request.parse_status = PARSE_BAD_REQUEST;
        return request;
    }
    strncpy(line, buffer, line_len);
    line[line_len] = '\0';

    char *method_str = strtok(line, " ");
    char *target_str = strtok(NULL, " ");
    char *version_str = strtok(NULL, " ");

    if (!method_str || !target_str || !version_str) {
        free(line);
        request.parse_status = PARSE_BAD_REQUEST;
        return request;
    }

    if (strcmp(method_str, METHOD_GET) == 0) request.method = GET;
    else if (strcmp(method_str, METHOD_POST) == 0) request.method = POST;
    else if (strcmp(method_str, METHOD_PUT) == 0) request.method = PUT;
    else if (strcmp(method_str, METHOD_DELETE) == 0) request.method = DELETE;
    else { free(line); request.parse_status = PARSE_UNSUPPORTED; return request; }

    request.target_path = malloc(strlen(target_str) + 1);
    if (!request.target_path) {
        free(line);
        request.parse_status = PARSE_BAD_REQUEST;
        return request;
    }

    strcpy(request.target_path, target_str);

    if (strcmp(version_str, "HTTP/1.1") == 0) request.version = HTTP_1_1;
    else if (strcmp(version_str, "HTTP/1.0") == 0) request.version = HTTP_1_0;
    else if (strcmp(version_str, "HTTP/0.9") == 0) request.version = HTTP_0_9;
    else if (strcmp(version_str, "HTTP/2") == 0)   request.version = HTTP_2;
    else if (strcmp(version_str, "HTTP/3") == 0)   request.version = HTTP_3;
    else { free(request.target_path); free(line); request.parse_status = PARSE_UNSUPPORTED; return request; }

    request.parse_status = PARSE_OK;

    free(line);

    return request;
}

/**
 * Frees the dynamically allocated memory in an HTTP request structure.
 * Specifically frees the target_path field and sets it to NULL.
 * 
 * @param request Pointer to the HTTP request structure to clean up
 */
void free_http_request(http_request_t *request) {
    if (request && request->target_path) {
        free(request->target_path);
        request->target_path = NULL;
    }
}
