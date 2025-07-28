/**
 * @file logger.hpp
 * @brief This file contains a logger class for logging messages.
 * @author Théo MAGNE
 * @date 2025-07-10
 */

#pragma once

#include <cstring>

namespace mark3
{
/**
 * @class Logger
 * @brief A logger class with some basic logging methods.
 * It takes a prefix in
 */
class Logger
{
    /// @brief The size of the prefix used in the logger.
    /// It uses the prefix given in the constructor and appends ' ' to fill the
    /// remaining space and a final null terminator.
    static constexpr int PREFIX_SIZE = 16;

    static constexpr int BUFFER_SIZE = 256;

  private:
    char m_buffer[BUFFER_SIZE];

  public:
    /**
     * @brief Constructor for the Logger class.
     * @param prefix The prefix to use for logging messages.
     */
    Logger(const char *prefix = nullptr);

    /**
     * @brief Log a message.
     * @param fmt The format string.
     * @param ... The arguments to format.
     */
    void msg(const char *fmt, ...);

    /**
     * @brief Log a debug message.
     * @param fmt The format string.
     * @param ... The arguments to format.
     */
    void d(const char *fmt, ...);

    /**
     * @brief Log an info message.
     * @param fmt The format string.
     * @param ... The arguments to format.
     */
    void i(const char *fmt, ...);

    /**
     * @brief Log a warning message.
     * @param fmt The format string.
     * @param ... The arguments to format.
     */
    void w(const char *fmt, ...);

    /**
     * @brief Log an error message.
     * @param fmt The format string.
     * @param ... The arguments to format.
     */
    void e(const char *fmt, ...);
};
} // namespace mark3
