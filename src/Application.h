#pragma once

#include "renderer/vulkan/VkRenderer.h"
#include "renderer/window/GlfwWindow.h"
#include "ui/ui.h"
#include "entt/entt.hpp"

namespace Engine {
    class Application {
    public:
        void run();

        ~Application();

    private:
        entt::registry registry;
        Renderer *renderer = new VkRenderer();
        Window *window = new GlfwWindow();
        PerspectiveCamera *camera = new PerspectiveCamera();
        Input *input;
        SystemsManager *systemsManager = new SystemsManager();
       // UI *ui;
        void init();

        void mainLoop();


    };

}