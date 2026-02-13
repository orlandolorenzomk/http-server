/**
 * @file http_request.h
 * @brief HTTP request data structures and types
 * 
 * Defines the data structures used to represent parsed HTTP requests,
 * including methods, versions, and parsing status.
 */

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

/**
 * HTTP request methods.
 * Represents the action to be performed on the resource.
 */
typedef enum {
    GET,     /** Retrieve a resource */
    POST,    /** Submit data to be processed */
    PUT,     /** Update a resource */
    DELETE   /** Remove a resource */
} http_method_t;

/**
 * HTTP protocol versions.
 * Indicates which version of HTTP the request uses.
 */
typedef enum {
    HTTP_0_9,  /** HTTP/0.9 - Simple protocol, no headers */
    HTTP_1_0,  /** HTTP/1.0 - Basic HTTP with headers */
    HTTP_1_1,  /** HTTP/1.1 - Persistent connections, chunked transfer */
    HTTP_2,    /** HTTP/2 - Binary protocol, multiplexing */
    HTTP_3     /** HTTP/3 - QUIC-based protocol */
} http_version_t;

/**
 * HTTP request parsing status.
 * Indicates the result of parsing an HTTP request.
 */
typedef enum {
    PARSE_OK,            /** Request parsed successfully */
    PARSE_BAD_REQUEST,   /** Request is malformed */
    PARSE_TOO_LARGE,     /** Request line exceeds maximum size */
    PARSE_UNSUPPORTED    /** Method or version not supported */
} http_parse_status_t;

/**
 * Represents a parsed HTTP request.
 * Contains all relevant information extracted from the request line.
 */
typedef struct {
    http_method_t method;           /** HTTP method (GET, POST, etc.) */
    char *target_path;              /** Request target (e.g., /, /auth, /users/1) */
    http_version_t version;         /** HTTP protocol version */
    http_parse_status_t parse_status; /** Result of parsing operation */
} http_request_t;

#endif // HTTP_REQUEST_H