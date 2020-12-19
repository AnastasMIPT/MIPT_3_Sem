#include "canvas.h"

Canvas::Canvas (Image* _pixels, const Rect& _trappings)
: AbstractWindow (_trappings), canvas_pixels (_pixels) {

    Rect rect_in_pixels = GEngine::system.convertAbstrToRealRect (trappings); // Don't work on Opengl because 
    view.setSizeByRect (rect_in_pixels);                                     //in OpenGl real_rect will be not in pixels   
}


Point2d Canvas::convertToCanvasCoords (const Point2d& screen_coords) {

    printf ("screen_coords = %lf, %lf\n", screen_coords.x, screen_coords.y);
    int pixel_x = view.off_x + 
        GEngine::system.convertHorizontalSizeToPixels (screen_coords.x - trappings.coords.x);
    int pixel_y = view.off_y +
        GEngine::system.convertVerticalSizeToPixels (trappings.coords.y + 
                                                     trappings.height - screen_coords.y);
//to do исправить баг: если изображение будет недостаточно большим, то traapigs.haight несет лишнее расстояние
    printf ("clac= %lf\n", trappings.coords.y + 
                                                     trappings.height - screen_coords.y);
    printf ("canvas coords = %d, %d\n", pixel_x, pixel_y);
    return {pixel_x, pixel_y};
}


void Canvas::draw () const {
    GEngine::system.drawImage (trappings.coords, *canvas_pixels, view);
}

void Canvas::setImage (Image* image) {
    canvas_pixels = image;
}

void Canvas::setPixel (size_t x, size_t y, const Pixel& pixel) {
    canvas_pixels->setPixel (x, y, pixel);
}

