#pragma once

#include "../pch.h"
#include "Model.h"
#include "../components/Texture.h"
#include "../logger/Logger.h"

namespace Engine {
    class AssetsManager {
        std::unordered_map<std::string ,std::vector<char>> files{};
    public:
        Model loadModel(const std::string &path);

        Texture loadTexture(const std::string &path);

        void freeTexture(Texture *texture);

        std::vector<char> loadFile(const std::string &path);
    };
}