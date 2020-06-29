#include "PerspectiveCameraSystem.h"

namespace Engine {
    void PerspectiveCameraSystem::update(const float &delta) {
        const float cameraSpeed = 2.0f * delta;
        if (input->isKeyPressed(Input::Key::W))
            camera->position += cameraSpeed * camera->front;
        if (input->isKeyPressed(Input::Key::S))
            camera->position -= cameraSpeed * camera->front;
        if (input->isKeyPressed(Input::Key::A))
            camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
        if (input->isKeyPressed(Input::Key::D))
            camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
        if (input->isKeyPressed(Input::Key::Q))
            camera->position -= glm::normalize(camera->up) * cameraSpeed;
        if (input->isKeyPressed(Input::Key::E))
            camera->position += glm::normalize(camera->up) * cameraSpeed;

        input->HideCursor(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT));


        auto mousePos = input->getMousePos();
        auto xpos = static_cast<float>(mousePos.x);
        auto ypos = static_cast<float>(mousePos.y);
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 1.0f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        if (!(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT) || firstFrame))
            return;

        firstFrame = false;
        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.z = sin(glm::radians(pitch));
        front.y = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera->front = glm::normalize(front);

    }

    PerspectiveCameraSystem::PerspectiveCameraSystem(PerspectiveCamera *camera, Input *input,
                                                     entt::registry& registry) : camera{camera},
                                                                                input{input},
                                                                                System(registry){}
}