#include "VkTexture.h"
#include <cstring>

namespace Engine {

    void VkTexture::loadTexture(Texture texture) {
    }

    void VkTexture::free(const VkDevice &device) {
        vkDestroySampler(device, sampler, nullptr);
        vkDestroyImageView(device, view, nullptr);
        vkDestroyImage(device, image, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }
}// namespace Engine