#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h"

int main (int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./http-server <port>\n");
        exit(EXIT_FAILURE);        
    }

    uint16_t port = (uint16_t) strtoul(argv[1], NULL, 10);
    start(port);

    exit(EXIT_SUCCESS);
}