#pragma once

#include <entt/entity/registry.hpp>
#include "System.h"
#include "../components/Transform.h"
#include "../components/Name.h"

#include "glm/gtc/quaternion.hpp"

namespace Engine {
    class EntitySystem : public System {
        entt::registry &registry;
        entt::entity entity;
    public:
        void update(const float &delta) override;

        EntitySystem(entt::registry &registry, const entt::entity& entity);
    };
}
