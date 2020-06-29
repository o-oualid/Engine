#pragma once

#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include "../../pch.h"
#include "Window.h"

namespace Engine {
    class GlfwWindow : public Window {
       int tempWidth= 0;
       int tempHeight= 0;
    public:
        GLFWwindow *window;

        void init(const std::string &title, int width, int height) override;

        bool shouldClose() override;

        void poolEvents() override;

        void getFramebufferSize(int &width, int &height) override;

        void createSurface(VkInstance instance, VkSurfaceKHR *surface) override;

        static void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
            // auto app = reinterpret_cast<HelloTriangleApplication *>(glfwGetWindowUserPointer(window));
            // app->framebufferResized = true;
        }

        std::vector<const char *> getRequiredExtensions() override;

        void waitEvents() override;

        ~GlfwWindow() override;

        bool isFramebufferResized() override;
    };
}