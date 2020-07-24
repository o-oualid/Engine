#pragma once

#include "MeshData.h"
#include "NodeData.h"
#include <vector>


namespace Engine {
    class Model {
    public:
        std::vector<NodeData> nodes{};
        std::vector<MeshData> meshData{};
    };
}// namespace Engine