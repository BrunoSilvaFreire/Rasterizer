#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H

#include <stdexcept>


struct Pixel {
public:
    uint8_t r, g, b, a;

    explicit Pixel(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0);
};

class Texture {
private:
    Pixel *buf;
    unsigned width, height;
public:
    Texture(unsigned width, unsigned height);

    void setPixel(unsigned x, unsigned y, const Pixel &color);

    Pixel &operator[](unsigned index);

};

#endif
