#include "logger.h"

namespace logger {

void Logger::log_error(const std::string& msg_str) noexcept {
    std::cout << "[ERROR]: " << msg_str << std::endl;
}

void Logger::log_info(const std::string& msg_str) noexcept {
    std::cout << "[INFO]: " << msg_str << std::endl;
}

void Logger::log_warn(const std::string& msg_str) noexcept {
    std::cout << "[WARN]: " << msg_str << std::endl;
}

}