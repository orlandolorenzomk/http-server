#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

typedef enum {
    GET,
    POST,
    PUT,
    DELETE
} http_method_t;

typedef enum {
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2,
    HTTP_3
} http_version_t;

typedef enum {
    PARSE_OK,
    PARSE_BAD_REQUEST,
    PARSE_TOO_LARGE,
    PARSE_UNSUPPORTED
} http_parse_status_t;


typedef struct {
    http_method_t method;
    char *target_path; // raw request target e.g.: /, /auth, /users/1/changePassword
    http_version_t version;
    http_parse_status_t parse_status;
} http_request_t;

#endif // HTTP_REQUEST_H