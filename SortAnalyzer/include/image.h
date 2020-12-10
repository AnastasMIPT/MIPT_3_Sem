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

    Image () = default;
    Image (size_t _width, size_t _height, const Pixel& default_pixel);
    Image (size_t _width, size_t _height, const std::vector<Pixel>& pixel_buf);
    
    // TO_DO constructor with param std::vector<Pixel>&&
    

    size_t getWidth  () const;
    size_t getHeight () const;
    Pixel  getPixel  (size_t x, size_t y) const;
    

    void  setPixel (size_t x, size_t y, const Pixel& pixel);

};

#endif