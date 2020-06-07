#pragma once

#include "System.h"
#include "../components/PerspectiveCamera.h"
#include "../io/Input.h"

class PerspectiveCameraSystem : public System {
private:
    PerspectiveCamera *camera;
    Input* input;
public:
    PerspectiveCameraSystem(PerspectiveCamera *camera, Input* input);

    void update(const float&  delta) override;
    virtual ~PerspectiveCameraSystem()= default;
};