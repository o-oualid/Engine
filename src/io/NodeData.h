#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <entt/entity/entity.hpp>
#include "../components/Transform.h"

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
}