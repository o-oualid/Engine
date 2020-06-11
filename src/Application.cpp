#include "Application.h"

namespace Engine {
    void Application::run() {
        init();
        mainLoop();
        cleanup();
    }

    void Application::init() {
        window->init("Game", 800, 600);
        input = new Input((dynamic_cast<GlfwWindow *>(window))->window);
        renderer->camera = camera;
        systemsManager->attachSystem(new PerspectiveCameraSystem(camera, input));
        renderer->window = window;
        renderer->init();
    }

    void Application::mainLoop() {
        float delta;
        float lastFrame = 0.0f;
        while (!window->shouldClose()) {
            auto currentTime = (float) glfwGetTime();
            delta = currentTime - lastFrame;
            lastFrame = currentTime;
            // std::cout<<1/delta<<std::endl;
            window->poolEvents();
            systemsManager->updateSystems(delta);
            renderer->draw();
        }
        renderer->waitIdle();
    }

    void Application::cleanup() {
        renderer->cleanup();
        window->cleanup();
        delete camera;
        delete systemsManager;
        delete input;
        delete renderer;
        delete window;
    }
}