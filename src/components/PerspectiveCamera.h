#pragma once

#include "../pch.h"
#include "Camera.h"
#include "Transform.h"

namespace Engine {
    class PerspectiveCamera {
    public:
        float aspect = 1.0f;
        float fov = glm::radians(45.0f);
        float zNear = 0.01f;
        float zFar = 100.0f;

        glm::mat4 view();

        glm::mat4 projection();
    };
}// namespace Engine