#pragma once

#include "Material.h"

namespace Engine {
    class MeshAttribute {
    public:
        uint32_t indexStart;
        uint32_t indexCount;
        uint32_t vertexStart;
        Material material{};
    };
}