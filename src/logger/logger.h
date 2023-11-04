#pragma once

#include <format>
#include <iostream>
#include <string>

namespace logger {

class Logger {
public:
    Logger() = default;
    ~Logger() = default;

    static void log_error(const std::string& msg_str) noexcept;
    static void log_info(const std::string& msg_str) noexcept;
    static void log_warn(const std::string& msg_str) noexcept;
};

#define LOG_ERROR(STR) Logger::log_error(STR)
#define LOG_INFO(STR) Logger::log_info(STR)
#define LOG_WARN(STR) Logger::log_warn(STR)

}