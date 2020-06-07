#pragma once

#include "vulkan/vulkan.h"

class Window {
public:

    virtual void init(const std::string &title, int width, int height) = 0;

    virtual bool shouldClose() = 0;

    virtual void poolEvent() = 0;

    virtual void cleanup() = 0;

    virtual void getFramebufferSize(int &width, int &height) = 0;

    virtual void createSurface(VkInstance instance, VkSurfaceKHR *surface) = 0;

    virtual void waitEvents()=0;

    virtual std::vector<const char *> getRequiredExtensions() = 0;
};
