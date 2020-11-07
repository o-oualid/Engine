#include "PerspectiveCamera.h"

namespace Engine {
    glm::mat4 PerspectiveCamera::view() {
        return glm::lookAt(pos, pos+front, up);
    }

    glm::mat4 PerspectiveCamera::projection() {
        return glm::perspective(fov, aspect, zNear, zFar);
    }

}// namespace Engine