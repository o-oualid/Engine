#pragma once
namespace Engine {
    class Texture {
    public:
        int width, height, channels;
        unsigned char *pixels;
    };
}// namespace Engine