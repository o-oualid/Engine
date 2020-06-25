#pragma once

#include <glm/detail/type_quat.hpp>
#include "glm/glm.hpp"

namespace Engine {
    class Transform {
    private:
        glm::mat4 transformMatrix;
    public:
        bool dirty= true;
        bool isDirty() const;

        glm::quat rotation = {1, 0, 0, 0};
        glm::vec3 location = {0, 0, 0};
        glm::vec3 scale = {1.0f, 1.0f, 1};

        glm::mat4 getTransformMatrix();
    };
}