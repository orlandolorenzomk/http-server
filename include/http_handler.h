/**
 * @file http_handler.h
 * @brief HTTP request handler and routing
 * 
 * Processes parsed HTTP requests and generates appropriate responses.
 * Implements request routing and business logic.
 */

#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "http_request.h"
#include "http_response.h"

/**
 * Handles an HTTP request and generates an appropriate response.
 * Routes requests based on method and path.
 * 
 * @param request Pointer to the parsed HTTP request
 * @return An http_response_t structure containing status, headers, and body
 */
http_response_t handle_request(http_request_t *request);

#endif