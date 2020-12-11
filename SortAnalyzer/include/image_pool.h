#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include "image.h"
#include "config.h"

class ImagePool {
    inline static std::vector<Image> images;
public:
    ImagePool () = delete;
    size_t addImage (const char* path);
    Image* getImageById (size_t id);
    void clear ();
};

#endif // IMAGE_POOL_H