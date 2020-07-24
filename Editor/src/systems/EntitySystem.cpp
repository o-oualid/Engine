#include "EntitySystem.h"

using namespace Engine;

EntitySystem::EntitySystem(entt::registry &registry) : System(registry) {}

void EntitySystem::update(const float &delta) {
    auto view = registry.view<Transform, Car>();

    for (auto entity: view) {
        auto &transform = view.get<Transform>(entity);
        auto &car = view.get<Car>(entity);
        transform.rotation = glm::rotate(transform.rotation, delta * car.speed, glm::vec3(0, 0, 1));
        transform.dirty = true;
    }
}
