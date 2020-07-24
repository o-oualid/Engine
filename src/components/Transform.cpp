#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

namespace Engine {
    glm::mat4 Transform::getTransformMatrix() {
        if (dirty) {
            transformMatrix = glm::mat4{1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};
            transformMatrix = glm::translate(transformMatrix, location);
            transformMatrix = transformMatrix * glm::mat4_cast(rotation);
            transformMatrix = glm::scale(transformMatrix, scale);
            dirty = !dirty;
        }
        return transformMatrix;
    }

    bool Transform::isDirty() const {
        return dirty;
    }
}// namespace Engine
