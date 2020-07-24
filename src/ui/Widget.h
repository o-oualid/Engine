#pragma once

#include "imgui.h"

namespace Engine {
    class Widget {
    public:
        virtual void init() = 0;

        virtual void draw() = 0;

        virtual ~Widget() = default;
    };
}// namespace Engine