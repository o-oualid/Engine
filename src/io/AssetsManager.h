#pragma once

#include "../pch.h"
#include "Model.h"
#include "../components/Texture.h"

namespace Engine {
    class AssetsManager {
    public:
        Model loadModel(const std::string &path);

        Texture loadTexture(const std::string &path);

        void freeTexture(Texture *texture);

        std::vector<char> loadFile(const std::string &path);
    };
}