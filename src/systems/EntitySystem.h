#pragma once

#include "System.h"
#include "../components/Transform.h"
#include "../components/Car.h"

#include "glm/gtc/quaternion.hpp"

namespace Engine {
    class EntitySystem : public System {
    public:
        void update(const float &delta) override;

        explicit EntitySystem(entt::registry &registry);

        ~EntitySystem() override = default;
    };
}
