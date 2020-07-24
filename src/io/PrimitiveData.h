#pragma once

#include "../Vertex.h"
#include "../components/Material.h"
#include <vector>

namespace Engine {
    class PrimitiveData {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        Material material{};
    };
}// namespace Engine