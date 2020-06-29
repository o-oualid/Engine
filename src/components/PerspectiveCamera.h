#pragma once

#include "Camera.h"
#include "../pch.h"
#include "Transform.h"

namespace Engine {
    class PerspectiveCamera {
    public:
        //  glm::vec3 position = glm::vec3(-0.0f, -2.0f, 0.0f);
        //glm::vec3 front = glm::normalize(glm::vec3(-0.0f, -1.0f, 0.0f));
        // glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
        float aspect = 1.0f;
        float fov = glm::radians(45.0f);
        float zNear = 0.01f;
        float zFar = 100.0f;

        glm::mat4 view();

        glm::mat4 projection();
    };
}