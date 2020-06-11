#include <cstring>
#include "VkTexture.h"
namespace Engine {

    void VkTexture::loadTexture(Texture texture) {
    }

    void VkTexture::free(const VkDevice &device) {
        vkDestroySampler(device, sampler, nullptr);
        vkDestroyImageView(device, view, nullptr);
        vkDestroyImage(device, image, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }
}