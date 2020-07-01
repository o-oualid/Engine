#include "ui.h"
#include "../renderer/window/GlfwWindow.h"

namespace Engine {
    void checkVkResult(VkResult result) {

    }

    UI::UI(VkRenderer *renderer) : renderer{renderer} {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        createDescriptorPool();
        createRenderPass();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForVulkan(dynamic_cast<GlfwWindow *>(renderer->window)->window, true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = renderer->instance;
        init_info.PhysicalDevice = renderer->physicalDevice;
        init_info.Device = renderer->device;
        init_info.QueueFamily = 404;
        init_info.Queue = renderer->graphicsQueue;
        init_info.PipelineCache = VK_NULL_HANDLE;
        init_info.DescriptorPool = descriptorPool;
        init_info.Allocator = nullptr;
        init_info.MinImageCount = 2;
        init_info.ImageCount = renderer->swapChainImages.size();
        init_info.CheckVkResultFn = checkVkResult;
        ImGui_ImplVulkan_Init(&init_info, renderPass);

        ImFont *font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Segoeui.ttf", 16.0f, NULL,
                                                    io.Fonts->GetGlyphRangesJapanese());

        VkCommandBuffer command_buffer = renderer->beginSingleTimeCommands();
        ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
        renderer->endSingleTimeCommands(command_buffer);

        createCommandPool(&commandPool, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        commandBuffers.resize(renderer->swapChainImages.size());
        createCommandBuffers(commandBuffers.data(), static_cast<uint32_t>(commandBuffers.size()), commandPool);
        createFrameBuffers();
    }

    void UI::createCommandPool(VkCommandPool *commandPool, VkCommandPoolCreateFlags flags) {
        VkCommandPoolCreateInfo commandPoolCreateInfo = {};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.queueFamilyIndex = renderer->findQueueFamilies(
                renderer->physicalDevice).graphicsFamily.value();
        commandPoolCreateInfo.flags = flags;

        if (vkCreateCommandPool(renderer->device, &commandPoolCreateInfo, nullptr, commandPool) != VK_SUCCESS) {
            throw std::runtime_error("Could not create graphics command pool");
        }
    }

    void
    UI::createCommandBuffers(VkCommandBuffer *commandBuffer, uint32_t commandBufferCount, VkCommandPool &commandPool) {
        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        commandBufferAllocateInfo.commandPool = commandPool;
        commandBufferAllocateInfo.commandBufferCount = commandBufferCount;
        vkAllocateCommandBuffers(renderer->device, &commandBufferAllocateInfo, commandBuffer);
    }

    void UI::createFrameBuffers() {
        VkImageView attachment[1]{};
        VkFramebufferCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        info.renderPass = renderPass;
        info.attachmentCount = 1;
        info.pAttachments = attachment;
        info.width = renderer->extent.width;
        info.height = renderer->extent.height;
        info.layers = 1;
        frameBuffers.resize(renderer->swapChainImages.size());
        for (uint32_t i = 0; i < renderer->swapChainImages.size(); i++) {
            attachment[0] = renderer->swapChainImageViews[i];
            vkCreateFramebuffer(renderer->device, &info, nullptr, &frameBuffers[i]);
        }
    }

    void UI::createDescriptorPool() {
        VkDescriptorPoolSize pool_sizes[] =
                {
                        {VK_DESCRIPTOR_TYPE_SAMPLER,                1000},
                        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
                        {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000},
                        {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000},
                        {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000},
                        {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000},
                        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000},
                        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000},
                        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
                        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
                        {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000}
                };
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t) IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        vkCreateDescriptorPool(renderer->device, &pool_info, nullptr, &descriptorPool);
    }

    void UI::createRenderPass() {
        VkAttachmentDescription attachment = {};
        attachment.format = renderer->swapChainImageFormat;
        attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment = {};
        color_attachment.attachment = 0;
        color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &color_attachment;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;  // or VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        info.attachmentCount = 1;
        info.pAttachments = &attachment;
        info.subpassCount = 1;
        info.pSubpasses = &subpass;
        info.dependencyCount = 1;
        info.pDependencies = &dependency;
        if (vkCreateRenderPass(renderer->device, &info, nullptr, &renderPass) != VK_SUCCESS)
            throw std::runtime_error("Could not create Dear ImGui's render pass");
    }

    void UI::render() {
        ImGui_ImplVulkan_SetMinImageCount(2);

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow();
        for (auto widget:widgets)
            widget->draw();
        ImGui::Render();

        renderFrame();
    }

    void UI::renderFrame() {
        uint32_t imageIndex = renderer->imageIndex;
        if (renderer->recreateBuffer) {
            for (auto framebuffer : frameBuffers)
                vkDestroyFramebuffer(renderer->device, framebuffer, nullptr);
            frameBuffers.clear();
            createFrameBuffers();
            renderer->recreateBuffer = false;
        }
        {
            vkResetCommandBuffer(commandBuffers[imageIndex], VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
            VkCommandBufferBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            vkBeginCommandBuffer(commandBuffers[imageIndex], &info);
        }
        {
            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};

            VkRenderPassBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            info.renderPass = renderPass;
            info.framebuffer = frameBuffers[imageIndex];
            info.renderArea.extent.width = renderer->extent.width;
            info.renderArea.extent.height = renderer->extent.height;
            info.clearValueCount = 1;
            info.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[imageIndex], &info, VK_SUBPASS_CONTENTS_INLINE);
        }
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffers[imageIndex]);
        vkCmdEndRenderPass(commandBuffers[imageIndex]);
        vkEndCommandBuffer(commandBuffers[imageIndex]);
        renderer->submitCommandBuffers.push_back(commandBuffers[imageIndex]);
    }

    UI::~UI() {
        for (auto framebuffer : frameBuffers)
            vkDestroyFramebuffer(renderer->device, framebuffer, nullptr);


        vkDestroyRenderPass(renderer->device, renderPass, nullptr);

        vkFreeCommandBuffers(renderer->device, commandPool,
                             static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
        vkDestroyCommandPool(renderer->device, commandPool, nullptr);

        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        vkDestroyDescriptorPool(renderer->device, descriptorPool, nullptr);
    }
}