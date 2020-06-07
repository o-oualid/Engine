#pragma once

#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include "../../pch.h"
#include "Window.h"

class GlfwWindow : public Window {
public:
    GLFWwindow *window;

    void init(const std::string &title, int width, int height) override;

    bool shouldClose() override;

    void poolEvents() override;

    void cleanup() override;

    void getFramebufferSize(int &width, int &height) override;

    void createSurface(VkInstance instance, VkSurfaceKHR *surface) override;

    static void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        // auto app = reinterpret_cast<HelloTriangleApplication *>(glfwGetWindowUserPointer(window));
        // app->framebufferResized = true;
    }

    std::vector<const char *> getRequiredExtensions() override;

    void waitEvents() override;
};
