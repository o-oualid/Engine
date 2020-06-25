#include "Application.h"
#include "systems/EntitySystem.h"

namespace Engine {
    void Application::run() {
        init();
        mainLoop();
    }

    void Application::init() {
        new VkRenderer(registry);
        window->init("Game", 800, 600);
        input = new Input((dynamic_cast<GlfwWindow *>(window))->window);
        renderer->camera = camera;
        systemsManager->attachSystem(new PerspectiveCameraSystem(camera, input));


        renderer->window = window;
        renderer->init();
        entt::entity entity = renderer->addModel("data/models/test.glb", glm::vec3(0, 5, 0));
        systemsManager->attachSystem(new EntitySystem(registry,entity));
        renderer->uploadData();
        // ui = new UI(static_cast<VkRenderer*>(renderer));
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
            //ui->update();
        }
        renderer->waitIdle();
    }

    Application::~Application() {
        delete camera;
        delete systemsManager;
        //delete ui;
        delete input;
        delete renderer;
        delete window;
    }
}