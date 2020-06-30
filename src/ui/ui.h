#include "imgui.h"
#include "imgui_impl_vulkan.h"
#include "imgui_impl_glfw.h"
#include "../renderer/vulkan/VkRenderer.h"

namespace Engine {
    class UI {
    private:
        VkRenderer* renderer;
        entt::registry &registry;
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
        explicit UI(VkRenderer *renderer,entt::registry &registry);

        ~UI();

        void render();

        void createFrameBuffers();

        void renderFrame();
    };
}