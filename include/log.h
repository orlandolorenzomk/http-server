#ifndef LOG_H
#define LOG_H

typedef enum {
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

extern char *type[];
extern char *colors[];

void log_write(log_level_t, const char *fmt, ...);

#endif // LOG_H