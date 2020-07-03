#pragma once

#include <string>
namespace Engine {
    class Logger {
    public:



        Logger() = default;

        virtual void info(std::string message) {};

        virtual void warn(std::string message) {};

        virtual void error(std::string message) {};

        virtual ~Logger() = default;
    };

    class Log{
    public:
        static inline Logger *logger;

    };
}