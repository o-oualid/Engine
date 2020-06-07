#pragma once

#include "../pch.h"
#include "../Vertex.h"

class Mesh {
public:
    std::vector<uint32_t> indices;
    std::vector<Vertex> vertices;
};
