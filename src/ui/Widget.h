#pragma once

#include "imgui.h"

namespace Engine {
    class Widget {
    public:
        virtual void draw() = 0;
    };
}