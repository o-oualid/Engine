#pragma once

#include "vulkan/vulkan.h"

namespace Engine {
    class Window {
    public:
        bool fullScreen= true;
        virtual void init(const std::string &title, int width, int height) = 0;

        virtual bool shouldClose() = 0;

        virtual void poolEvents() = 0;

        virtual void getFramebufferSize(int &width, int &height) = 0;

        virtual void createSurface(VkInstance instance, VkSurfaceKHR *surface) = 0;

        virtual void waitEvents() = 0;

        virtual std::vector<const char *> getRequiredExtensions() = 0;

        virtual bool isFramebufferResized()=0;

        virtual ~Window() =default;
    };
}