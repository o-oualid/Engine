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

        glm::vec3 pos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up    = glm::vec3(0.0f, 1.0f,  0.0f);

        glm::mat4 view();

        glm::mat4 projection();
    };
}// namespace Engine