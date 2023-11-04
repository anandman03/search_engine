#pragma once

#include <format>
#include <iostream>
#include <string>

namespace logger {

enum class LogLevel {ERROR=1, WARN, INFO, DEBUG};

class Logger {
public:
    Logger() = default;
    ~Logger() = default;

    inline static LogLevel log_level = LogLevel::WARN;

    static void log_debug(const std::string& msg_str) noexcept;
    static void log_error(const std::string& msg_str) noexcept;
    static void log_info(const std::string& msg_str) noexcept;
    static void log_warn(const std::string& msg_str) noexcept;

private:
    static void log_message(const std::string& msg_type, const std::string& msg_str);
};

#define LOG_ERROR(STR) Logger::log_error(STR)
#define LOG_INFO(STR) Logger::log_info(STR)
#define LOG_WARN(STR) Logger::log_warn(STR)

}