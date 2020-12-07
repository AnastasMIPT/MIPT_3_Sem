#include "image.h"

Image::Image (size_t _height, size_t _width, const Pixel& default_pixel)
: pixels (_height * _width, default_pixel), width (_width), height (_height) {}

Pixel Image::getPixel (size_t x, size_t y) const {
    return pixels[y * width + x];
}

void Image::setPixel (size_t x, size_t y, const Pixel& pixel) {
    pixels[y * width + x] = pixel;
}

