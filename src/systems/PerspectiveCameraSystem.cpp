#include "PerspectiveCameraSystem.h"

namespace Engine {
    void PerspectiveCameraSystem::update(const float &delta) {
        auto &transform = registry.get<Transform>(camera);
        if (input->isKeyPressed(Input::Key::UP))speed += 1 * delta;
        if (input->isKeyPressed(Input::Key::DOWN))speed -= 1 * delta;

        const float cameraSpeed = speed * delta;
        glm::vec3 forward = glm::rotate(transform.rotation, glm::vec3{0, 0, -1});
        glm::vec3 left = glm::rotate(transform.rotation, glm::vec3{1, 0, 0});

        if (input->isKeyPressed(Input::Key::W))
            transform.location += cameraSpeed * forward;
        if (input->isKeyPressed(Input::Key::S))
            transform.location -= cameraSpeed * forward;
        if (input->isKeyPressed(Input::Key::A))
            transform.location -= cameraSpeed * left;
        if (input->isKeyPressed(Input::Key::D))
            transform.location += cameraSpeed * left;
        if (input->isKeyPressed(Input::Key::Q))
            transform.location.z -= cameraSpeed;
        if (input->isKeyPressed(Input::Key::E))
            transform.location.z += cameraSpeed;

        input->HideCursor(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT));
        transform.dirty = true;

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

        float sensitivity = 0.01f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        if (!(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT) || firstFrame)) return;

        firstFrame = false;
        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        transform.rotation = glm::quat(glm::vec3(pitch, 0, -yaw));


    }

    PerspectiveCameraSystem::PerspectiveCameraSystem(entt::entity camera, Input *input,
                                                     entt::registry &registry) : camera{camera},
                                                                                 input{input},
                                                                                 System(registry) {}
}