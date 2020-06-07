#pragma once

#include "../pch.h"
#include "Actor.h"

class Camera: public Actor {

public:
    float aspect=1.0f;

    virtual glm::mat4 projection() = 0;

    virtual glm::mat4 view() = 0;


    virtual ~Camera() = 0 {};
};