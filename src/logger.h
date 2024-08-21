#ifndef utils_logger_h
#define utils_logger_h

#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#endif

typedef enum
{
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_COUNT
} TextColor;

void _log(char *prefix, char *msg, TextColor text_color, ...)
{
    va_list args;
    va_start(args, text_color);

    static char *Text_Color_Table[TEXT_COLOR_COUNT] = {
        "\x1b[30m", // TEXT_COLOR_BLACK
        "\x1b[31m", // TEXT_COLOR_RED
        "\x1b[32m", // TEXT_COLOR_GREEN
        "\x1b[33m", // TEXT_COLOR_YELLOW
        "\x1b[37m", // TEXT_COLOR_WHITE
    };

    char format_buffer[8192] = {};
    sprintf(format_buffer, "%s %s %s \033[0m", Text_Color_Table[text_color], prefix, msg);

    char text_buffer[8192] = {};
    sprintf(text_buffer, format_buffer, args);

    puts(text_buffer);
    va_end(args);
}

#define LOG_TRACE(msg, ...) _log("TRACE: ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define LOG_WARN(msg, ...) _log("WARNING: ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define LOG_ERROR(msg, ...) _log("ERROR: ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);

#define LOG_ASSERT(x, msg, ...)            \
    {                                      \
        if (!(x))                          \
        {                                  \
            LOG_ERROR(msg, ##__VA_ARGS__); \
            DEBUG_BREAK();                 \
            LOG_ERROR("Assertion Hit!");   \
        }                                  \
    }

#endif