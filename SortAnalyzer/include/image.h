#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <cstdint>
#include <vector>

using ab::Pixel;


class Image {
    std::vector<Pixel> pixels;
    size_t width  = 0;
    size_t height = 0;

public:

    Image (size_t _height, size_t _width, const Pixel& default_pixel);
    
    Pixel getPixel (size_t x, size_t y) const;
    void  setPixel (size_t x, size_t y, const Pixel& pixel);
};

#endif