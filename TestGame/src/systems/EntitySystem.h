#pragma once

#include <systems/System.h>
#include <components/Transform.h>
#include "../components/Car.h"

#include "glm/gtc/quaternion.hpp"

class EntitySystem : public Engine::System {
public:
    void update(const float &delta) override;

    explicit EntitySystem(entt::registry &registry);

    ~EntitySystem() override = default;
};

