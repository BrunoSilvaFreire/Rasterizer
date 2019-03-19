#include <gflags/gflags.h>
#include <texture.h>

DECLARE_string(outputfile);

#define OUTPUT_HEIGHT 1080
#define OUTPUT_WIDTH 1920

int main() {
    Texture texture(OUTPUT_WIDTH, OUTPUT_HEIGHT);

    return 0;
}