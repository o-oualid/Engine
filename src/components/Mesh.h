#pragma once

#include <vector>
#include "MeshAttribute.h"

namespace Engine {
    class Mesh {
    public:
        std::vector<MeshAttribute>attributes{};
    };
}
