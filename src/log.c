#include "log.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

/* Log level string representations */
char *type[] = {
    "INFO",
    "DEBUG",
    "WARN",
    "ERROR"
};

/* ANSI color codes for each log level */
char *colors[] = {
    "\x1b[0m",     // INFO - white
    "\x1b[32m",    // DEBUG - green
    "\x1b[1;33m",  // WARN - yellow
    "\x1b[31m"     // ERROR - red
};

/**
 * Writes a formatted log message with timestamp and color-coded level.
 * 
 * @param level The severity level of the log message
 * @param fmt Format string (printf-style) for the log message
 * @param ... Variable arguments for the format string
 */
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