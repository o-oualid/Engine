#pragma once

#include "entt/entt.hpp"
#include "logger/TerminalLogger.h"
#include "renderer/vulkan/VkRenderer.h"
#include "renderer/window/GlfwWindow.h"
#include "ui/ui.h"

namespace Engine {
    class Application {
        std::string name;
        TerminalLogger logger = TerminalLogger{};

    public:
        void run();

        Application(std::string name);

        ~Application();

    protected:
        entt::registry registry{};
        Renderer *renderer = new VkRenderer(registry);
        Window *window = new GlfwWindow();
        UI *ui;
        Input *input;
        SystemsManager *systemsManager = new SystemsManager();

        virtual void init() = 0;
    };

}// namespace Engine