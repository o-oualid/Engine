#include "EditorLogger.h"

void EditorLogger::info(std::string message) {
    errors.push_back({Error::Type::Info, message});
}

void EditorLogger::warn(std::string message) {
    errors.push_back({Error::Type::Warn, message});

}

void EditorLogger::error(std::string message) {
    errors.push_back({Error::Type::Error, message});

}

void EditorLogger::draw() {
    ImGui::Begin("Logger");
    for (const Error &error:errors) {
        ImVec4 color;
        switch (error.type) {
            case Error::Type::Info:
                color = {0.5, 1, 0.5, 1};
                break;
            case Error::Type::Warn:
                color = {1, 1, 0, 1};
                break;
            case Error::Type::Error:
                color = {1, 0.5, 0.5, 1};

                break;
        }
        ImGui::TextColored(color, "%s",  error.message.c_str());
    }
    ImGui::End();
}

