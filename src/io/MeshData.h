#pragma once

#include "../Vertex.h"
#include "../components/Material.h"
#include "PrimitiveData.h"
#include <cstdint>
#include <vector>

namespace Engine {
    class MeshData {
    public:
        std::vector<PrimitiveData> primitives{};
    };
}// namespace Engine