#pragma once

#include <vector>
#include "../Vertex.h"
#include "../components/Material.h"

namespace Engine {
    class PrimitiveData {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        Material material{};
    };
}