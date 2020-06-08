#pragma once

#include "System.h"
#include "../components/PerspectiveCamera.h"
#include "../io/Input.h"

class PerspectiveCameraSystem : public System {
private:
    PerspectiveCamera *camera;
    Input* input;

    bool firstMouse = true;
    float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch =  0.0f;
    float lastX = 1920.f;
    float lastY =  1080.0f;

public:
    PerspectiveCameraSystem(PerspectiveCamera *camera, Input* input);

    void update(const float&  delta) override;
    virtual ~PerspectiveCameraSystem()= default;
};