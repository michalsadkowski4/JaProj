#include "Logger.h"
#include <iostream>

void Logger::LogInfo(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}

void Logger::LogError(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}