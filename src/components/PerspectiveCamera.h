#pragma once

#include "Camera.h"
#include "../pch.h"
namespace Engine {
    class PerspectiveCamera : public Camera {
    public:
        glm::vec3 position = glm::vec3(2.0f, 2.0f, 2.0f);
        glm::vec3 front = glm::normalize(glm::vec3(-0.5f, -0.5f, -2.0f));
        glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

        float fov = glm::radians(45.0f);
        float zNear = 0.01f;
        float zFar = 100.0f;

        glm::mat4 view() override;

        glm::mat4 projection() override;

        ~PerspectiveCamera() override = default;
    };
}