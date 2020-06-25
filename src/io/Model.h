#pragma once

#include <vector>
#include "MeshData.h"
#include "NodeData.h"


namespace Engine {
    class Model {
    public:
        std::vector<NodeData> nodes{};
        std::vector<MeshData> meshData{};
    };
}