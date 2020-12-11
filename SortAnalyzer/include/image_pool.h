#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include "image.h"
#include "config.h"

class ImagePool {
    enum DefaultImages {
        SCROLL_BUTTON_UP,
        SCROLL_BUTTON_DOWN,
        SCROLL_BUTTON_LEFT,
        SCROLL_BUTTON_RIGHT,
        PENCIL,
        A_PENCIL,
        ERASER,
        DEFAULT_IMAGES_COUNT
    };
    inline static std::vector<Image> images = std::vector<Image> (DEFAULT_IMAGES_COUNT);
    
public:
    ImagePool () = delete;
    static size_t addImage (const char* path);
    static Image* getImageById (size_t id);
    static void clear ();

    static void loadDefaultImages ();
};

#endif // IMAGE_POOL_H