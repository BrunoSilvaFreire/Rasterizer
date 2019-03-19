#include <texture.h>

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

Texture::Texture(unsigned width, unsigned height) {
    buf = new Pixel[width * height];
    Texture::height = height;
    Texture::width = width;

}

void Texture::setPixel(unsigned x, unsigned y, const Pixel &color) {
    buf[x + y * width] = color;
}

Pixel &Texture::operator[](const unsigned index) {
    return buf[index];
}
