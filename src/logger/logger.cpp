#include "logger.h"

namespace logger {

void Logger::log_debug(const std::string& msg_str) noexcept {
    if (log_level >= LogLevel::DEBUG) log_message("DEBUG", msg_str);
}

void Logger::log_error(const std::string& msg_str) noexcept {
    if (log_level >= LogLevel::ERROR) log_message("ERROR", msg_str);
}

void Logger::log_info(const std::string& msg_str) noexcept {
    if (log_level >= LogLevel::INFO) log_message("INFO", msg_str);
}

void Logger::log_warn(const std::string& msg_str) noexcept {
    if (log_level >= LogLevel::WARN) log_message("WARN", msg_str);
}

void Logger::log_message(const std::string& msg_type, const std::string& msg_str) {
    std::cout << "[" << msg_type << "]: " << msg_str << std::endl;
}

}