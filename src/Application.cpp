#include "Application.h"
#include "components/Relationship.h"
#include "components/Name.h"

namespace Engine {

    Application::Application() {
        registry.create();
        entt::entity camera = registry.create();
        registry.emplace<PerspectiveCamera>(camera);
        Transform cameraTransform{};
        cameraTransform.location = {0.0f, 0.0f, 0.5f};
        cameraTransform.rotation = {0.707107f, 0.707107f, 0.0f, 0.0f};
        registry.emplace<Transform>(camera, cameraTransform);
        registry.emplace<Name>(camera, Name{"PerspectiveCamera"});
        registry.emplace<Relationship>(camera, Relationship{camera});
        renderer = new VkRenderer(registry);
        window->init("Game", 800, 600);
        input = new Input((dynamic_cast<GlfwWindow *>(window))->window);

        renderer->window = window;
        renderer->camera = camera;
        renderer->init();
        ui = new UI(dynamic_cast<VkRenderer *>(renderer));
        systemsManager->attachSystem(new PerspectiveCameraSystem(camera, input, registry));

    }

    void Application::run() {
        float delta;
        float lastFrame = 0.0f;
        while (!window->shouldClose()) {
            auto currentTime = (float) glfwGetTime();
            delta = currentTime - lastFrame;
            lastFrame = currentTime;
            // std::cout<<1/delta<<std::endl;
            window->poolEvents();
            systemsManager->updateSystems(delta);
            if (renderer->render()) {
                ui->render();
                renderer->present();
            }
        }
        renderer->waitIdle();
    }

    Application::~Application() {
        delete systemsManager;
        delete input;
        delete ui;
        delete renderer;
        delete window;
    }
}