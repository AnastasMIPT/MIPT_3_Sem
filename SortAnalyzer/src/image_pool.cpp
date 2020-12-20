#include "image_pool.h"
#include "config.h"


size_t ImagePool::addImage (const char* path) {
    images.push_back (GEngine::system.loadImageFromFile (path));
    return images.size () - 1;
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

void ImagePool::loadDefaultImages () {
    images[DEF_IMAGES::PENCIL]              = GEngine::system.loadImageFromFile
                                            ("./resources/images/pencil.png");
    
    images[DEF_IMAGES::ERASER]              = GEngine::system.loadImageFromFile
                                            ("./resources/images/eraser.png");

    images[DEF_IMAGES::BOX_BLUR]            = GEngine::system.loadImageFromFile
                                            ("./plugins/BoxBlur/icon.png");

    images[DEF_IMAGES::COLOR_FILTER]        = GEngine::system.loadImageFromFile
                                            ("./plugins/ColorFilter/icon.png");                                        


    images[DEF_IMAGES::A_PENCIL]            = GEngine::system.loadImageFromFile
                                            ("./resources/images/a_pencil.png");

    images[DEF_IMAGES::A_ERASER]            = GEngine::system.loadImageFromFile
                                            ("./resources/images/a_eraser.png");
    
    images[DEF_IMAGES::A_BOX_BLUR]          = GEngine::system.loadImageFromFile
                                            ("./plugins/BoxBlur/icon.png");

    images[DEF_IMAGES::A_COLOR_FILTER]        = GEngine::system.loadImageFromFile
                                            ("./plugins/ColorFilter/icon.png");


    images[DEF_IMAGES::SCROLL_BUTTON_UP]    = GEngine::system.loadImageFromFile 
                                            ("./resources/images/scroll_but.png");
    
    images[DEF_IMAGES::SCROLL_BUTTON_DOWN]  = GEngine::system.loadImageFromFile
                                            ("./resources/images/scroll_but_down.png");

    images[DEF_IMAGES::SCROLL_BUTTON_LEFT]  = GEngine::system.loadImageFromFile
                                            ("./resources/images/scroll_but_left.png");

    images[DEF_IMAGES::SCROLL_BUTTON_RIGHT] = GEngine::system.loadImageFromFile
                                            ("./resources/images/scroll_but_right.png");

    
}