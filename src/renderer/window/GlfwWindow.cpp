#include "GlfwWindow.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
    void GlfwWindow::init(const std::string &title, int width, int height) {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        tempWidth = width;
        tempHeight = height;
    }

    bool GlfwWindow::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void GlfwWindow::poolEvents() {
        glfwPollEvents();
    }

    GlfwWindow::~GlfwWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void GlfwWindow::getFramebufferSize(int &width, int &height) {
        glfwGetFramebufferSize(window, &width, &height);
    }

    std::vector<const char *> GlfwWindow::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef NDEBUG
#else
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

        return extensions;
    }

    void GlfwWindow::createSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface!");
    }

    void GlfwWindow::waitEvents() {
        glfwWaitEvents();
    }


    bool GlfwWindow::isFramebufferResized() {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        if (width != tempWidth || height != tempHeight) {
            tempWidth = width;
            tempHeight = height;
            return true;
        }
        return false;
    }
}