#pragma once



#include "../pch.h"
#include "../components/Mesh.h"
#include "../components/Texture.h"

class AssetsManager {
public:
    Mesh loadModel(const std::string &path);
    Texture loadTexture(const std::string &path);
    void freeTexture(Texture* texture);

    std::vector<char> loadFile(const std::string &path);
};
