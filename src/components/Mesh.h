#pragma once

#include "MeshAttribute.h"
#include <vector>

namespace Engine {
    class Mesh {
    public:
        std::vector<MeshAttribute> attributes{};
    };
}// namespace Engine
