#pragma once

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include <glm/detail/type_quat.hpp>
namespace Engine {
    class Transform {
    private:
        glm::mat4 transformMatrix;

    public:
        bool dirty = true;
        bool isDirty() const;

        glm::vec3 location = {0, 0, 0};
        glm::quat rotation = {1, 0, 0, 0};
        glm::vec3 scale = {1, 1, 1};

        glm::mat4 getTransformMatrix();
        glm::mat4 getGlobalTransform(entt::registry &registry);
    };
}// namespace Engine