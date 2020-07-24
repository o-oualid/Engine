#pragma once

#include "../../components/Texture.h"
#include "vulkan/vulkan.h"

namespace Engine {
    struct VkTexture {

        VkImage image;
        VkDeviceMemory memory;
        VkImageView view;
        VkSampler sampler;
        int width, height;

        void loadTexture(Texture texture);

        void free(const VkDevice &device);
    };
}// namespace Engine