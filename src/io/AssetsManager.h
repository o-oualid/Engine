#pragma once

#include "../components/Texture.h"
#include "../logger/Logger.h"
#include "../pch.h"
#include "Model.h"

namespace Engine {
    class AssetsManager {
        std::unordered_map<std::string, std::vector<char>> files{};

    public:
        Model loadModel(const std::string &path);

        Texture loadTexture(const std::string &path);

        void freeTexture(Texture *texture);

        std::vector<char> loadFile(const std::string &path);
    };
}// namespace Engine