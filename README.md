# HTTP Server in C

A lightweight, multi-threaded HTTP/1.1 server implementation in C for educational purposes. This project demonstrates fundamental concepts in network programming, socket programming, HTTP protocol handling, and concurrent request processing.

## Learning Objectives

This project covers:
- Socket programming with Berkeley sockets API
- HTTP/1.1 request parsing and response formatting
- Multi-threaded server architecture using POSIX threads
- Memory management in C
- Error handling and validation
- Logging and debugging techniques

## Features

- **Multi-threaded**: Handles multiple concurrent client connections using pthreads
- **HTTP/1.1 Support**: Parses and responds to HTTP requests
- **Request Parsing**: Supports GET, POST, PUT, and DELETE methods
- **Proper HTTP Responses**: Returns appropriate status codes (200, 400, 404)
- **Color-coded Logging**: Timestamped logs with different levels (INFO, DEBUG, WARN, ERROR)
- **Port Validation**: Ensures requested port is available before binding
- **Memory Safe**: Proper cleanup of allocated resources

## Project Structure

```
http-server/
├── include/              # Header files
│   ├── http_handler.h    # Request handler interface
│   ├── http_parser.h     # HTTP request parser
│   ├── http_request.h    # HTTP request structures
│   ├── http_response.h   # HTTP response structures
│   ├── http_server.h     # Server core interface
│   ├── log.h            # Logging utilities
│   ├── str_utils.h      # String manipulation utilities
│   └── validation.h     # Validation functions
├── src/                 # Source files
│   ├── http_handler.c   # Request handling logic
│   ├── http_parser.c    # HTTP parsing implementation
│   ├── http_server.c    # Server socket and threading logic
│   ├── log.c           # Logging implementation
│   ├── main.c          # Entry point
│   ├── str_utils.c     # String utilities
│   └── validation.c    # Port and socket validation
├── test/               # Testing utilities
│   └── client.py       # Python test client
├── Makefile           # Build configuration
└── README.md         # This file
```

## Building the Project

### Prerequisites

- GCC compiler
- POSIX-compliant system (Linux, macOS, WSL)
- Make build tool
- pthread library

### Compilation

```bash
# Build the project
make

# Clean build artifacts
make clean

# Clean and rebuild
make rebuild
```

The compiled binary will be named `http-server`.

## Running the Server

```bash
./http-server <port>
```

**Example:**
```bash
./http-server 8080
```

The server will:
1. Validate the port (must be ≥ 1024)
2. Check if the port is available
3. Start listening for connections
4. Log all activity with timestamps

**Sample Output:**
```
[14:23:45] [INFO] Starting TCP Server on port 8080
```

## Testing the Server

### Using cURL

```bash
# Simple GET request
curl http://localhost:8080/

# Verbose output
curl -v http://localhost:8080/

# Non-existent route (returns 404)
curl http://localhost:8080/notfound
```

### Using the Python Test Client

The project includes a multi-client test utility:

```bash
# Single client, single request
./test/client.py 127.0.0.1 8080

# Multiple concurrent clients
./test/client.py 127.0.0.1 8080 -c 5

# Multiple clients, multiple messages each
./test/client.py 127.0.0.1 8080 -c 3 -r 2

# Custom message prefix
./test/client.py 127.0.0.1 8080 -c 4 -m "hello"
```

**Client Options:**
- `-c, --clients`: Number of concurrent clients (default: 1)
- `-r, --repeat`: Number of messages per client (default: 1)
- `-m, --message`: Custom message prefix (appends client number)

### Using Web Browser

Simply navigate to:
```
http://localhost:8080/
```

## Technical Details

### HTTP Methods Supported

- `GET` - Retrieve resource
- `POST` - Submit data
- `PUT` - Update resource
- `DELETE` - Remove resource

### HTTP Versions Supported

- HTTP/0.9
- HTTP/1.0
- HTTP/1.1
- HTTP/2 (parsing only)
- HTTP/3 (parsing only)

### Status Codes

- `200 OK` - Request successful
- `400 Bad Request` - Malformed request
- `404 Not Found` - Resource not found

### Content Types

- `text/plain` - Default response type
- `text/html` - HTML content

### Request Handling Flow

1. Client connects → Server accepts connection
2. Server spawns new thread for client
3. Thread reads HTTP request into buffer
4. Parser validates and extracts request components
5. Handler processes request and generates response
6. Server sends HTTP headers and body
7. Connection closed, resources freed

### Concurrency Model

- **Main thread**: Accepts incoming connections
- **Worker threads**: Each client connection handled in separate detached thread
- **Thread pool**: Dynamic (threads created on-demand)
- **Max payload size**: 8192 bytes

## Logging System

The logging system provides color-coded, timestamped output:

```c
log_write(LOG_INFO, "Server started on port %d", port);
log_write(LOG_WARN, "Resource usage high");
log_write(LOG_ERROR, "Failed to bind socket");
log_write(LOG_DEBUG, "Request parsed: %s", path);
```

**Log Levels:**
- `LOG_INFO` - General information (white)
- `LOG_DEBUG` - Debug information (green)
- `LOG_WARN` - Warnings (yellow)
- `LOG_ERROR` - Errors (red)

## Example Requests and Responses

### Valid GET Request

**Request:**
```http
GET / HTTP/1.1
Host: localhost:8080
```

**Response:**
```http
HTTP/1.1 200 OK
Content-Length: 13
Content-Type: text/plain
Connection: close

Hello, world!
```

### Invalid Request

**Request:**
```http
GET /unknown HTTP/1.1
Host: localhost:8080
```

**Response:**
```http
HTTP/1.1 404 Not Found
Content-Length: 9
Content-Type: text/plain
Connection: close

Not Found
```

## Error Handling

The server handles various error conditions:

- **Invalid port**: Ports below 1024 rejected
- **Port in use**: Checks availability before binding
- **Malformed requests**: Returns 400 Bad Request
- **Memory allocation failures**: Gracefully skips connection
- **Thread creation failures**: Logs error and continues accepting

## Extending the Project

### Adding New Routes

Edit [http_handler.c](src/http_handler.c):

```c
if (request->method == GET && strcmp(request->target_path, "/newroute") == 0) {
    response.status_code = OK;
    const char *msg = "New route response!";
    response.content_length = strlen(msg);
    response.body = malloc(response.content_length + 1);
    if (response.body) {
        strcpy(response.body, msg);
    }
}
```

### Adding Request Headers Parsing

Extend the parser in [http_parser.c](src/http_parser.c) to extract headers after the request line.

### Adding Response Headers

Modify the response construction in [http_server.c](src/http_server.c) to include additional headers like `Server`, `Date`, etc.

## Common Issues

### Port Already in Use
```bash
[ERROR] Given port 8080 is not available. Check if any process is using that port.
```
**Solution:** Use a different port or kill the process using `lsof -ti:8080 | xargs kill`

### Permission Denied (ports < 1024)
```bash
[ERROR] Given port 80 is not valid.
```
**Solution:** Use ports ≥ 1024 or run with sudo (not recommended)

### Connection Refused
**Solution:** Ensure the server is running and firewall allows the connection

## Resources

- [RFC 7230 - HTTP/1.1 Message Syntax](https://tools.ietf.org/html/rfc7230)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

## License

This is an educational project. Feel free to use, modify, and learn from it.

## Contributing

This is a learning project! Contributions, improvements, and suggestions are welcome. Consider adding:

- Request body parsing
- Query parameter extraction
- Cookie support
- Keep-alive connections
- Static file serving
- HTTPS/TLS support
- Configuration file support
- Thread pool implementation
- Request/response middleware
- Rate limiting

---
