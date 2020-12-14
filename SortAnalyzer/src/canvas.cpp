#include "canvas.h"

Canvas::Canvas (Image* _pixels, const Rect& _trappings)
: AbstractWindow (_trappings), canvas_pixels (_pixels) {}


Point2d Canvas::convertToCanvasCoords (const Point2d& screen_coords) {
    return screen_coords;
}


void Canvas::draw () const {
    GEngine::system.drawImageInArea (trappings, *canvas_pixels);
}