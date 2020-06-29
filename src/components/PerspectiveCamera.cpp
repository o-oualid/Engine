#include "PerspectiveCamera.h"

namespace Engine {
    glm::mat4 PerspectiveCamera::view() {
        throw std::out_of_range("function not implemented");
        return glm::mat4{};
    }

    glm::mat4 PerspectiveCamera::projection() {
        return glm::perspective(fov, aspect, zNear, zFar);
    }

}