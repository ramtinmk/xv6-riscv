#ifndef __CUSTOM_LOGGER_H__
#define __CUSTOM_LOGGER_H__

// Enum for log levels (can be used by callers)
typedef enum {
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_INFO = 3
} LogLevel;

// Function prototypes

void log_message(int level, const char *message); // Log a message

// Optional: Define simple macros for easier logging calls
#define log_error(msg)   log_message(LOG_LEVEL_ERROR, msg)
#define log_warning(msg) log_message(LOG_LEVEL_WARNING, msg)
#define log_info(msg)    log_message(LOG_LEVEL_INFO, msg)

// Optional: Variable to control global log level (declared in .c file)
// extern int kernel_log_level;

#endif // __CUSTOM_LOGGER_H__