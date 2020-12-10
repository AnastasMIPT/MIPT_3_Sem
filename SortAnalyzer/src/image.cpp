#include "image.h"

Image::Image (size_t _width, size_t _height, const Pixel& default_pixel)
: pixels (_height * _width, default_pixel), width (_width), height (_height) {}

Image::Image (size_t _width, size_t _height, const std::vector<Pixel>& pixel_buf)
: pixels (pixel_buf), width (_width), height (_height) {}

Pixel Image::getPixel (size_t x, size_t y) const {
    return pixels[y * width + x];
}

void Image::setPixel (size_t x, size_t y, const Pixel& pixel) {
    pixels[y * width + x] = pixel;
}

size_t Image::getWidth () const {
    return width;
}

size_t Image::getHeight () const {
    return height;
}

const Pixel* Image::getPixelArray () const {
    return &pixels[0];
}

