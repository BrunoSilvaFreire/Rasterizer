#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H

#include <stdexcept>


struct Pixel {
public:
    const static Pixel white;
    uint8_t r, g, b, a;

    explicit Pixel(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0);
};

class Texture {
public:
    static void drawLine(Texture &texture, const Pixel &color, unsigned x0, unsigned x1, unsigned y0, unsigned y1) {
        bool steep = false;
        if (x1 - x0 < y1 - y0) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        float derror = std::abs(dy / float(dx));
        float error = 0;
        int y = y0;
        for (int x = x0; x <= x1; x++) {
            if (steep) {
                texture.set(static_cast<unsigned int>(y), static_cast<unsigned int>(x), color);
            } else {
                texture.set(x, y, color);
            }
            error += derror;
            if (error > .5) {
                y += (y1 > y0 ? 1 : -1);
                error -= 1.;
            }
        }
    }

private:
    Pixel *buf;
    unsigned width, height;
public:
    Texture(unsigned width, unsigned height);

    void set(unsigned x, unsigned y, const Pixel &color);

    Pixel &operator[](unsigned index);

};

#endif
