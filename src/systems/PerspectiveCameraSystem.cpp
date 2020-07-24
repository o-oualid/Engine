#include "PerspectiveCameraSystem.h"

namespace Engine {
    void PerspectiveCameraSystem::update(const float &delta) {
        auto &transform = registry.get<Transform>(camera);
        if (input->isKeyPressed(Input::Key::UP))
            speed += 1 * delta;
        if (input->isKeyPressed(Input::Key::DOWN))
            speed -= 1 * delta;

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
            transform.location.y -= cameraSpeed;
        if (input->isKeyPressed(Input::Key::E))
            transform.location.y += cameraSpeed;

        input->HideCursor(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT));

        transform.dirty = true;

        auto mousePos = input->getMousePos();
        auto xPos = static_cast<float>(mousePos.x);
        auto yPos = static_cast<float>(mousePos.y);
        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        float sensitivity = 0.01f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        if ((input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT))) {
            //    float pitch = glm::pitch(transform.rotation) + yOffset;
            //    float yaw = glm::yaw(transform.rotation) - xOffset;
            //    float roll = glm::roll(transform.rotation);
            //
            //    transform.rotation = glm::quat(glm::vec3(pitch, yaw, roll));

            transform.rotation = glm::rotate(transform.rotation, -xOffset, glm::vec3{0, 1, 0});
            transform.rotation = glm::rotate(transform.rotation, yOffset, glm::vec3{1, 0, 0});
        }
    }

    PerspectiveCameraSystem::PerspectiveCameraSystem(entt::entity camera, Input *input, entt::registry &registry)
        : camera{camera}, input{input}, System(registry) {}
}// namespace Engine