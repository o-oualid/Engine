#pragma once

#include "../components/Transform.h"
#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Engine {
    class NodeData {
    public:
        uint32_t meshId;
        Transform transform{};
        std::string name;
        std::vector<int> children;
        entt::entity parent{entt::null};
        entt::entity self{entt::null};
    };
}// namespace Engine