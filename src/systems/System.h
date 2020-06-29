#pragma once
#include <entt/entity/registry.hpp>

namespace Engine {
    class System {
    protected:
        entt::registry &registry;
    public:
        System(entt::registry& registry) : registry{registry}{}
        virtual void update(const float &delta) = 0;
        virtual ~System() = default;
    };
}