#pragma once

#include <entt/entity/entity.hpp>
#include <entt/fwd.hpp>

namespace Engine {
    class Relationship {
    public:
        entt::entity parent{entt::null};
    };
}// namespace Engine
