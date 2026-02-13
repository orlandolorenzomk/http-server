/**
 * @file http_response.h
 * @brief HTTP response data structures and types
 * 
 * Defines the data structures used to represent HTTP responses,
 * including status codes, content types, and response bodies.
 */

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stddef.h>

/**
 * HTTP status codes.
 * Indicates the result of processing the HTTP request.
 */
typedef enum {
    OK = 200,            /** Request succeeded */
    NOT_FOUND = 404,     /** Requested resource not found */
    BAD_REQUEST = 400    /** Malformed or invalid request */
} http_status_code_t;

/**
 * HTTP content types.
 * Specifies the media type of the response body.
 */
typedef enum {
    TEXT_PLAIN,  /** Plain text response */
    TEXT_HTML    /** HTML document response */
} http_content_type_t;

/**
 * Represents an HTTP response.
 * Contains all information needed to send a response to the client.
 */
typedef struct {
    http_status_code_t status_code;    /** HTTP status code (200, 404, etc.) */
    size_t content_length;             /** Length of response body in bytes */
    http_content_type_t content_type;  /** Media type of the response */
    char *body;                        /** Response body (dynamically allocated) */
} http_response_t;

#endif // HTTP_RESPONSE_H