#pragma once

#include "Logger.h"

namespace Engine {
    class TerminalLogger final : public Logger {
    public:
        void info(std::string message) final;

        void warn(std::string message) final;

        void error(std::string message) final;

        ~TerminalLogger() final = default;
    };
}// namespace Engine