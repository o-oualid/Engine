#pragma once

#include "vulkan/vulkan.h"
#include "../../components/Texture.h"

struct VkTexture { ;

    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
    VkSampler sampler;

    void loadTexture(Texture texture);

    void free(const VkDevice &device);
};