#include "canvas.h"

Canvas::Canvas (Image* _pixels, const Rect& _trappings)
: AbstractWindow (_trappings), canvas_pixels (_pixels) {

    Rect rect_in_pixels = GEngine::system.convertAbstrToRealRect (trappings); // Don't work on Opengl because 
    view.setSizeByRect (rect_in_pixels);                                     //in OpenGl real_rect will be not in pixels   
}


Point2d Canvas::convertToCanvasCoords (const Point2d& screen_coords) {
    return screen_coords;
}


void Canvas::draw () const {
    GEngine::system.drawImageInArea (trappings, *canvas_pixels, true, view);
}

void Canvas::setImage (Image* image) {
    canvas_pixels = image;
}

