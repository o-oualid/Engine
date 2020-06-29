#pragma once

#include "../pch.h"

namespace Engine {
    class Camera {

    public:
        glm::vec3 position;

        float aspect = 1.0f;

        virtual glm::mat4 projection() = 0;

        virtual glm::mat4 view() = 0;

        virtual ~Camera() = default;
    };
}