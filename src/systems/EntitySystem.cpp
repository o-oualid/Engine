#include "EntitySystem.h"

namespace Engine {
    EntitySystem::EntitySystem(entt::registry &registry, const entt::entity &entity) : registry{registry},
                                                                                       entity{entity} {

    }

    void EntitySystem::update(const float &delta) {
        auto &transform = registry.get<Transform>(entity);
        auto name = registry.get<Name>(entity).name;
        transform.rotation = glm::rotate(transform.rotation, 2 * delta, glm::vec3(0, 0, 1));
        transform.dirty = true;
    }
}