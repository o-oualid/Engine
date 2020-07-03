#include <iostream>
#include "TerminalLogger.h"

namespace Engine {
    void TerminalLogger::info(std::string message) {
        std::cout << "\x1B[32m Info: " << message << "\033[0m" << std::endl;
    }

    void TerminalLogger::warn(std::string message) {
        std::cout << "\x1B[33m Warn: " << message << "\033[0m" << std::endl;
    }

    void TerminalLogger::error(std::string message) {
        //std::cout << "\x1B[31m Error: " << message << "\033[0m" << std::endl;
        throw std::runtime_error(message);
    }
}