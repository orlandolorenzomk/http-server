#include "log.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

char *type[] = {
    "INFO",
    "DEBUG",
    "WARN",
    "ERROR"
};

char *colors[] = {
    "\x1b[0m",
    "\x1b[32m",
    "\x1b[1;33m",
    "\x1b[31m"
};

void log_write(log_level_t level, const char *fmt, ...) {
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    
    va_list args;
    va_start(args, fmt);
    
    printf("%s[%02d:%02d:%02d] [%s]\x1b[0m ",
           colors[level],
           local->tm_hour,
           local->tm_min,
           local->tm_sec,
           type[level]);
    
    vprintf(fmt, args);
    printf("\n");
    
    va_end(args);
}