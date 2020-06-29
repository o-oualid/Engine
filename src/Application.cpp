#include "Application.h"
#include "systems/EntitySystem.h"
#include "components/Relationship.h"

namespace Engine {
    void Application::run() {
        init();
        mainLoop();
    }

    void Application::init() {
        entt::entity camera = registry.create();
        registry.emplace<PerspectiveCamera>(camera);
        registry.emplace<Transform>(camera);

        new VkRenderer(registry);
        window->init("Game", 800, 600);
        input = new Input((dynamic_cast<GlfwWindow *>(window))->window);

        renderer->window = window;
        renderer->camera=camera;
        renderer->init();
        renderer->addModel("data/models/test2.glb");
        systemsManager->attachSystem(new PerspectiveCameraSystem(camera, input, registry));

        entt::entity entity = renderer->addModel("data/models/test.glb");
        registry.emplace<Car>(entity, Car{0.5f});
        entt::entity entity1 = renderer->addModel("data/models/test3.glb");
        registry.emplace<Car>(entity1, Car{0.45f});
        entt::entity entity2 = renderer->addModel("data/models/test4.glb");
        registry.emplace<Car>(entity2, Car{0.4f});
        registry.emplace<Relationship>(camera,Relationship{entity1});
        systemsManager->attachSystem(new EntitySystem(registry));

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
        delete systemsManager;
        //delete ui;
        delete input;
        delete renderer;
        delete window;
    }
}