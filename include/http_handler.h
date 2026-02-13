#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "http_request.h"
#include "http_response.h"

http_response_t handle_request(http_request_t *request);

#endif