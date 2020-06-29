#include "PerspectiveCamera.h"

namespace Engine {
    glm::mat4 PerspectiveCamera::view() {
        return glm::lookAt(position, position + front, up);


    }

    glm::mat4 PerspectiveCamera::projection() {
        return glm::perspective(fov, aspect, zNear, zFar);
    }
}