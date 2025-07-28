/**
 * @file logger.cpp
 * @author Théo MAGNE
 * @date 2025-07-10
 * @see logger.hpp
 */

#include "logger.hpp"

#include <cstdarg>
#include <cstdio>

namespace mark3
{

#define LOG_ANSI_CYAN "\033[36m"
#define LOG_ANSI_YELLOW "\033[33m"
#define LOG_ANSI_RED "\033[31m"
#define LOG_ANSI_GREEN "\033[32m"
#define LOG_ANSI_BLUE "\033[34m"
#define LOG_ANSI_MAGENTA "\033[35m"
#define LOG_ANSI_WHITE "\033[37m"
#define LOG_ANSI_BRIGHT_CYAN "\033[96m"
#define LOG_ANSI_RESET "\033[0m"
#define LOG_ANSI_BOLD "\033[1m"

#define COMMON_MSG_VSNPRINTF(_fmt, _msg_size)                                  \
    va_list args;                                                              \
    va_start(args, _fmt);                                                      \
    size_t _msg_size                                                           \
        = std::vsnprintf(                                                      \
              m_buffer + PREFIX_SIZE, BUFFER_SIZE - PREFIX_SIZE, _fmt, args)   \
          + PREFIX_SIZE;                                                       \
    va_end(args);

extern "C"
{
    // We expect this function to be defined elsewhere in the project.
    // TODO(tmagne): Use a macro to define the function name.
    void log_puts(const char *str, int len);
}

Logger::Logger(const char *prefix)
{

    size_t prefix_len = prefix ? std::strlen(prefix) : 0;

    for (size_t i = 0; i < PREFIX_SIZE; ++i)
    {
        if (i < prefix_len)
        {
            m_buffer[i] = prefix[i];
        }
        else
        {
            m_buffer[i] = ' ';
        }
    }
}

void Logger::msg(const char *fmt, ...)
{
    COMMON_MSG_VSNPRINTF(fmt, msg_size);
    log_puts(m_buffer, msg_size);
}

void Logger::d(const char *fmt, ...)
{
    log_puts((const char *)LOG_ANSI_BRIGHT_CYAN,
             sizeof(LOG_ANSI_BRIGHT_CYAN) - 1);
    COMMON_MSG_VSNPRINTF(fmt, msg_size);
    log_puts(m_buffer, msg_size);
}

void Logger::i(const char *fmt, ...)
{
    log_puts((const char *)LOG_ANSI_GREEN, sizeof(LOG_ANSI_GREEN) - 1);
    COMMON_MSG_VSNPRINTF(fmt, msg_size);
    log_puts(m_buffer, msg_size);
}

void Logger::w(const char *fmt, ...)
{
    log_puts((const char *)LOG_ANSI_YELLOW, sizeof(LOG_ANSI_YELLOW) - 1);
    COMMON_MSG_VSNPRINTF(fmt, msg_size);
    log_puts(m_buffer, msg_size);
}

void Logger::e(const char *fmt, ...)
{
    log_puts((const char *)LOG_ANSI_RED, sizeof(LOG_ANSI_RED) - 1);
    COMMON_MSG_VSNPRINTF(fmt, msg_size);
    log_puts(m_buffer, msg_size);
}

} // namespace mark3
