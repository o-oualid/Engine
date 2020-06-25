#pragma once

#include <cstdint>
#include <vector>
#include "../Vertex.h"
#include "PrimitiveData.h"
#include "../components/Material.h"

namespace Engine {
    class MeshData {
    public:
        std::vector<PrimitiveData> primitives{};
    };
}