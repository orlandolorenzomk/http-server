/**
 * @file log.h
 * @brief Logging system with color-coded output and timestamps
 * 
 * Provides a simple but effective logging system with different severity levels
 * and color-coded console output for better readability.
 */

#ifndef LOG_H
#define LOG_H

/**
 * Log severity levels.
 * Controls the type and color of log output.
 */
typedef enum {
    LOG_INFO,   /** General information messages (white) */
    LOG_DEBUG,  /** Debug information (green) */
    LOG_WARN,   /** Warning messages (yellow) */
    LOG_ERROR   /** Error messages (red) */
} log_level_t;

/** Array of log level names */
extern char *type[];

/** Array of ANSI color codes for each log level */
extern char *colors[];

/**
 * Writes a formatted log message with timestamp and color-coded level.
 * 
 * @param level The severity level of the log message
 * @param fmt Format string (printf-style) for the log message
 * @param ... Variable arguments for the format string
 */
void log_write(log_level_t, const char *fmt, ...);

#endif // LOG_H