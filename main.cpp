#include "tgaimage.h"

#include <cmath>
#include <algorithm>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool rot = false;
    if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
        std::swap(y0, x0);
        std::swap(y1, x1);
        rot = true;
    }
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    for (int y = y0; y <= y1; y++) {
        float t = (y - y0)*1./(y1 - y0);
        int x = x0*(1.-t) + x1*t;
        if (rot) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        } 
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, red);
    line(80, 40, 13, 20, image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
