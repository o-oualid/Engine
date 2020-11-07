#pragma once

#include <glm/vec4.hpp>

namespace Engine {
    class Material {
    public:
        glm::vec4 color{};
        uint32_t useColor = 0;
    };
}// namespace Engine