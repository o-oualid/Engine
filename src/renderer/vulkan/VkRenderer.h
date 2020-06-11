#pragma once

#include "../Renderer.h"

#include "../../pch.h"
#include "../../components/Camera.h"
#include "../../systems/PerspectiveCameraSystem.h"
#include "../../systems/SystemsManager.h"
#include "../../Vertex.h"
#include "../../io/AssetsManager.h"
#include "VkTexture.h"

namespace Engine {
    const std::string MODEL_PATH = "models/viking_room.obj";
    const std::string TEXTURE_PATH = "textures/viking_room.png";

    const int MAX_FRAMES_IN_FLIGHT = 2;

    const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif


    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    class VkRenderer : public Renderer {
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkTexture texture;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;

        bool framebufferResized = false;


        AssetsManager assetsManager{};


        bool no = false;


        void init() override;

        void draw() override;

        void waitIdle() override;

        void cleanup() override;

        void cleanupSwapChain();


        void recreateSwapChain();

        void createInstance();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

        void setupDebugMessenger();

        void createSurface();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain();

        void createImageViews();

        void createRenderPass();

        void createDescriptorSetLayout();

        void createGraphicsPipeline();

        void createFrameBuffers();

        void createCommandPool();

        void createDepthResources();

        VkFormat
        findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling,
                            VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        void createTextureImage();

        void createTextureImageView();

        void createTextureSampler();

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void
        createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void loadModel();

        void createVertexBuffer();

        void createIndexBuffer();


        void createUniformBuffers();

        void createDescriptorPool();

        void createDescriptorSets();

        void
        createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                     VkDeviceMemory &bufferMemory);

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createCommandBuffers();

        void createSyncObjects();

        void updateUniformBuffer(size_t currentImage);


        VkShaderModule createShaderModule(const std::vector<char> &code);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        bool isDeviceSuitable(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        std::vector<const char *> getRequiredExtensions() {
            return window->getRequiredExtensions();
        }

        bool checkValidationLayerSupport();


        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                            void *pUserData) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }
    };
}