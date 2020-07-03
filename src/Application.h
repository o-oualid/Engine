#pragma once

#include "renderer/vulkan/VkRenderer.h"
#include "renderer/window/GlfwWindow.h"
#include "ui/ui.h"
#include "entt/entt.hpp"
#include "logger/TerminalLogger.h"

namespace Engine {
    class Application {
        TerminalLogger logger = TerminalLogger{};
    public:
        void run();

        Application();

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

}