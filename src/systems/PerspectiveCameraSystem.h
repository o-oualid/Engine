#pragma once

#include "../components/PerspectiveCamera.h"
#include "../io/Input.h"
#include "System.h"
#include <glm/gtx/quaternion.hpp>

namespace Engine {
    class PerspectiveCameraSystem final : public System {
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
    };
}// namespace Engine