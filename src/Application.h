#pragma once

#include "renderer/vulkan/VkRenderer.h"
#include "renderer/window/GlfwWindow.h"

class Application {
public:
    void run();

private:
    Renderer *renderer = new VkRenderer();
    Window *window = new GlfwWindow();
    PerspectiveCamera *camera = new PerspectiveCamera();;
    Input *input;
    SystemsManager *systemsManager = new SystemsManager();

    void init();

    void mainLoop();

    void cleanup();

};

