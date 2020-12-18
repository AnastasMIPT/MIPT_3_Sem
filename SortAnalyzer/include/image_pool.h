#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include "image.h"

namespace DEF_IMAGES {
    enum {
        PENCIL,
        ERASER,
        A_PENCIL,
        A_ERASER,
        SCROLL_BUTTON_UP,
        SCROLL_BUTTON_DOWN,
        SCROLL_BUTTON_LEFT,
        SCROLL_BUTTON_RIGHT,
        DEFAULT_IMAGES_COUNT
    };

};

class ImagePool {
    
    inline static std::vector<Image> images = std::vector<Image> (DEF_IMAGES::DEFAULT_IMAGES_COUNT);
    
public:
    ImagePool () = delete;
    static size_t addImage (const char* path);
    static Image* getImageById (size_t id);
    static void clear ();

    static void loadDefaultImages ();
};

#endif // IMAGE_POOL_H