#include "imgui.h"
#include "imgui_impl_vulkan.h"
#include "imgui_impl_glfw.h"
#include "../renderer/vulkan/VkRenderer.h"

namespace Engine {
    class UI {
    private:
        VkRenderer &renderer;
        VkDescriptorPool descriptorPool;
        VkRenderPass renderPass;

        void createDescriptorPool();
        void createRenderPass();
        void renderFrame();
        void presentFrame();

    public:
        explicit UI(VkRenderer &renderer);
        void draw();
    };
}