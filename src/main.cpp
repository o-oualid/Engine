
#include "renderer/vulkan/VkRenderer.h"
#include "renderer/window/GlfwWindow.h"


class Application {
public:
    Renderer *renderer = new VkRenderer();
    Window *window = new GlfwWindow();

    void run() {
        window->init("Game", 800, 600);
        init();

        renderer->window = window;

        renderer->init();
        mainLoop();
        renderer->cleanup();
        window->cleanup();
    }

private:
    PerspectiveCamera *camera;
    Input *input;
    SystemsManager *systemsManager = new SystemsManager;

    void init() {

        input = new Input((dynamic_cast<GlfwWindow*>(window))->window);
        camera = new PerspectiveCamera();
        renderer->camera=camera;
        systemsManager->attachSystem(new PerspectiveCameraSystem(camera, input));

    }


    void mainLoop() {
        float delta = 0.0f;
        float lastFrame = 0.0f;
        while (!window->shouldClose()) {

            auto currentTime = (float) glfwGetTime();
            delta = currentTime - lastFrame;
            lastFrame = currentTime;
            window->poolEvent();
            systemsManager->updateSystems(delta);
            renderer->draw();
        }
        renderer->waitIdle();
    }


};



int main() {
    Application app;

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}