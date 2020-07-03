#pragma once

#include <logger/Logger.h>
#include <imgui.h>
#include <vector>

struct Error {
    enum class Type {
        Info, Warn, Error
    };
    Type type;
    std::string message;
};

class EditorLogger final : public Engine::Logger {
    std::vector<Error> errors{};
public:
    void info(std::string message) override;

    void warn(std::string message) override;

    void error(std::string message) override;

    void draw();

    ~EditorLogger() override = default;
};


