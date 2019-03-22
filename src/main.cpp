#include <gflags/gflags.h>
#include <texture.h>
#include <tiny_obj_loader.h>
#include <iostream>
#include <png.h>

DECLARE_string(modelFile);
DECLARE_string(outputFile);

#define OUTPUT_HEIGHT 1080
#define OUTPUT_WIDTH 1920


void drawLine(
        Texture &texture,
        tinyobj::attrib_t &mesh,
        tinyobj::index_t first,
        tinyobj::index_t second
) {

    auto v0x = mesh.vertices[first.vertex_index];
    auto v0y = mesh.vertices[first.vertex_index + 1];
    auto v1x = mesh.vertices[second.vertex_index];
    auto v1y = mesh.vertices[second.vertex_index + 1];
    auto minX = std::min(v0x, v1x);
    auto maxX = std::max(v0x, v1x);
    auto minY = std::min(v0y, v1y);
    auto maxY = std::max(v0y, v1y);
    auto x0 = static_cast<unsigned int>((minX + 1.) * OUTPUT_WIDTH / 2.);
    auto y0 = static_cast<unsigned int>((minY + 1.) * OUTPUT_HEIGHT / 2.);
    auto x1 = static_cast<unsigned int>((maxX + 1.) * OUTPUT_WIDTH / 2.);
    auto y1 = static_cast<unsigned int>((maxY + 1.) * OUTPUT_HEIGHT / 2.);
    Texture::drawLine(texture, Pixel::white, x0, x1, y0, y1);
}

void saveToPNG(Texture &texture, const char string[8]);

int main() {
    Texture texture(OUTPUT_WIDTH, OUTPUT_HEIGHT);
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> meshes;
    std::vector<tinyobj::material_t> materials;
    std::string err, warn;
    /*auto s = fLS::FLAGS_modelFile;
    if (s.empty()) {
        throw std::runtime_error("No file.");
    }*/
    tinyobj::LoadObj(&attrib, &meshes, &materials, &warn, &err, "/home/bruno/CLionProjects/Rasterizer/res/model.obj");

    for (auto &shape : meshes) {
        std::cout << "Loaded shape " << shape.name << "." << std::endl;
        auto &mesh = shape.mesh;
        auto &indices = mesh.indices;
        for (int i = 0; i < indices.size(); i += 3) {
            auto &first = indices[i];
            auto &second = indices[i + 1];
            auto &third = indices[i + 2];
            drawLine(texture, attrib, first, second);
            drawLine(texture, attrib, second, third);
            drawLine(texture, attrib, third, first);
        }
    }
    saveToPNG(texture, "out.png");
    return 0;
}

void saveToPNG(Texture &texture, const char *string) {
    png_structp png_ptr;
    png_infop info_ptr;
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr == nullptr) {
        throw std::runtime_error("Unable to create png struct.");
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        throw std::runtime_error("Unable to create png info.");
    }
    png_set_IHDR(png_ptr, info_ptr, OUTPUT_WIDTH, OUTPUT_HEIGHT, 8,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    auto row = new png_byte[OUTPUT_HEIGHT * OUTPUT_WIDTH * 3];
    for (int y = 0; y < OUTPUT_HEIGHT; ++y) {
        for (int x = 0; x < OUTPUT_WIDTH; ++x) {
            auto i = (x + y * OUTPUT_HEIGHT) * 3;
            auto p = texture[i];
            row[i] = p.r;
            row[i + 1] = p.g;
            row[i + 2] = p.b;
        }
        png_write_row(png_ptr, row);
    }

    delete[] row;
}