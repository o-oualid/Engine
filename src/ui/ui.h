#include "imgui.h"
#include "imgui_impl_vulkan.h"
#include "imgui_impl_glfw.h"
#include "../renderer/vulkan/VkRenderer.h"
#include "Widget.h"

namespace Engine {
    class UI {
    public:
        std::vector<Widget*> widgets{};
    private:
        VkRenderer *renderer;
        VkDescriptorPool descriptorPool;
        VkRenderPass renderPass;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers{};
        std::vector<VkFramebuffer> frameBuffers{};


        void createDescriptorPool();

        void createCommandPool(VkCommandPool *commandPool, VkCommandPoolCreateFlags flags);

        void createCommandBuffers(VkCommandBuffer *commandBuffer, uint32_t commandBufferCount,
                                  VkCommandPool &commandPool);

        void createRenderPass();

    public:
        explicit UI(VkRenderer *renderer);

        ~UI();

        void render();

        void createFrameBuffers();

        void renderFrame();
    };
}