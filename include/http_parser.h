/**
 * @file http_parser.h
 * @brief HTTP request parsing utilities
 * 
 * Provides functionality to parse raw HTTP requests into structured data.
 * Includes constants for HTTP methods, versions, and status messages.
 */

#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "http_request.h"
#include <stddef.h>

/** Maximum length of HTTP request line in bytes */
#define MAX_REQUEST_LINE 1024

/** End of line marker for HTTP (CRLF) */
#define EOR "\r\n"

/* HTTP Method string literals */
#define METHOD_GET "GET"       /** GET method string */
#define METHOD_POST "POST"     /** POST method string */
#define METHOD_PUT "PUT"       /** PUT method string */
#define METHOD_DELETE "DELETE" /** DELETE method string */

/* HTTP Version string literals */
#define VERSION_HTTP_0_9 "HTTP/0.9" /** HTTP/0.9 version string */
#define VERSION_HTTP_1_0 "HTTP/1.0" /** HTTP/1.0 version string */
#define VERSION_HTTP_1_1 "HTTP/1.1" /** HTTP/1.1 version string */
#define VERSION_HTTP_2   "HTTP/2"   /** HTTP/2 version string */
#define VERSION_HTTP_3   "HTTP/3"   /** HTTP/3 version string */

/* HTTP Status message strings */
#define STATUS_OK_MSG         "OK"          /** 200 OK message */
#define STATUS_BAD_REQUEST_MSG "Bad Request" /** 400 Bad Request message */
#define STATUS_NOT_FOUND_MSG   "Not Found"   /** 404 Not Found message */

/**
 * Parses an HTTP request from a buffer.
 * Extracts method, target path, and HTTP version from the request line.
 * 
 * @param buffer The buffer containing the raw HTTP request
 * @param length The length of the buffer
 * @return An http_request_t structure with parsed data and parse status
 */
http_request_t parse_http_request(const char *buffer, size_t length);

/**
 * Frees the dynamically allocated memory in an HTTP request structure.
 * 
 * @param request Pointer to the HTTP request structure to clean up
 */
void free_http_request(http_request_t *request);

#endif // HTTP_PARSER_H
