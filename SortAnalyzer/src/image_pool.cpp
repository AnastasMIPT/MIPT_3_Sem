#include "image_pool.h"



size_t ImagePool::addImage (const char* path) {
    images.push_back (GEngine::system.loadImageFromFile (path));
    return images.size ();
}

void ImagePool::clear () {
    images.clear ();
}

Image* ImagePool::getImageById (size_t id) {
    if (id >= images.size ()) {
        return NULL;
    }
    return &images[id];
}