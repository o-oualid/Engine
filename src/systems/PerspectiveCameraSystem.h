#pragma once

#include "../components/PerspectiveCamera.h"
#include "../io/Input.h"
#include "System.h"
#include <glm/gtx/quaternion.hpp>

namespace Engine {
    class PerspectiveCameraSystem final : public System, Input::InputListener {
    private:
        entt::entity camera;
        Input *input;
        float speed = 1;

        bool firstMouse = true;
        float lastX = 0;
        float lastY = 0;

    public:
        PerspectiveCameraSystem(entt::entity camera, Input *input, entt::registry &registry);

        void update(const float &delta) override;

        ~PerspectiveCameraSystem() final = default;

    private:
        bool onMouseMoved(float x, float y) override;
        bool MouseKeyPressed(Input::MouseKey key) override;
        bool onKeyPressed(Input::Key key) override;
        bool onKeyReleased(Input::Key key) override;
    };
}// namespace Engine