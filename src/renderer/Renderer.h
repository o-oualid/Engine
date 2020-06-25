#pragma once

#include "../components/Camera.h"
#include "window/Window.h"

namespace Engine {
    class Renderer {
    public:

        Camera *camera;
        Window *window;


        virtual void init() = 0;

        virtual void draw() = 0;

        virtual void waitIdle() = 0;

        virtual entt::entity addModel(const std::string &path, const glm::vec3 &loaction) = 0;
        virtual void uploadData()=0;
        virtual ~Renderer() = 0 {};

    };
}