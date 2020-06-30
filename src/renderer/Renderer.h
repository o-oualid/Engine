#pragma once

#include "../components/Camera.h"
#include "window/Window.h"

namespace Engine {
    class Renderer {
    public:

        entt::entity camera;
        Window *window;
        bool vSync = true;

        virtual void init() = 0;

        virtual bool render() = 0;

        virtual void present() = 0;

        virtual void waitIdle() = 0;

        virtual entt::entity addModel(const std::string &path) = 0;

        virtual void uploadData() = 0;

        virtual ~Renderer() = default;

    };
}