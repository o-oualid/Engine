#include "PerspectiveCameraSystem.h"
namespace Engine {
    void PerspectiveCameraSystem::update(const float &delta) {
        auto &perspectiveCamera = registry.get<PerspectiveCamera>(camera);
        if (input->isKeyPressed(Input::Key::UP))
            speed += 1 * delta;
        if (input->isKeyPressed(Input::Key::DOWN))
            speed -= 1 * delta;

        const float cameraSpeed = speed * delta;

        if (input->isKeyPressed(Input::Key::W))
            perspectiveCamera.pos += cameraSpeed * perspectiveCamera.front;
        if (input->isKeyPressed(Input::Key::S))
            perspectiveCamera.pos -= cameraSpeed * perspectiveCamera.front;
        if (input->isKeyPressed(Input::Key::A))
            perspectiveCamera.pos -= cameraSpeed * glm::normalize(glm::cross(perspectiveCamera.front, perspectiveCamera.up));
        if (input->isKeyPressed(Input::Key::D))
            perspectiveCamera.pos += cameraSpeed * glm::normalize(glm::cross(perspectiveCamera.front, perspectiveCamera.up));

        if (input->isKeyPressed(Input::Key::Q))
            perspectiveCamera.pos.y -= cameraSpeed;
        if (input->isKeyPressed(Input::Key::E))
            perspectiveCamera.pos.y += cameraSpeed;
    }

    PerspectiveCameraSystem::PerspectiveCameraSystem(entt::entity camera, Input *input, entt::registry &registry)
        : camera{camera}, input{input}, System(registry) {
        input->addMouseListener(this);
    }
    bool PerspectiveCameraSystem::onMouseMoved(float x, float y) {
        auto &perspectiveCamera = registry.get<PerspectiveCamera>(camera);
        input->HideCursor(input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT));
        float xPos = x;
        float yPos = y;

        static float yaw = -90.0f;
        static float pitch = 0.0f;

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw));
            direction.z = sin(glm::radians(yaw));
            firstMouse = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        float sensitivity = 0.1f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        if (input->isMouseKeyPressed(Input::MouseKey::BUTTON_RIGHT)) {


            yaw += xOffset;
            pitch += yOffset;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            perspectiveCamera.front = glm::normalize(direction);
        }
        return false;
    }
    bool PerspectiveCameraSystem::MouseKeyPressed(Input::MouseKey key) { return false; }
    bool PerspectiveCameraSystem::onKeyPressed(Input::Key key) { return false; }
    bool PerspectiveCameraSystem::onKeyReleased(Input::Key key) { return false; }

}// namespace Engine