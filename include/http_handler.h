#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "http_request.h"
#include "http_response.h"

#define BAD_REQUEST_MSG "400 Bad Request"
#define NOT_FOUND_MSG   "404 Not Found"

http_response_t handle_request(http_request_t *request);

#endif