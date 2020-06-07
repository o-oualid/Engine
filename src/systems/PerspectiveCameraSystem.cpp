#include "PerspectiveCameraSystem.h"

void PerspectiveCameraSystem::update(const float &delta) {
    const float cameraSpeed = 2.0f * delta;
    if (input->isKeyPressed(Input::Key::W))
        camera->position += cameraSpeed * camera->front;
    if (input->isKeyPressed(Input::Key::S))
        camera->position -= cameraSpeed * camera->front;
    if (input->isKeyPressed(Input::Key::A))
        camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
    if (input->isKeyPressed(Input::Key::D))
        camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
}

PerspectiveCameraSystem::PerspectiveCameraSystem(PerspectiveCamera *camera, Input *input) : camera{camera},
                                                                                            input{input} {}