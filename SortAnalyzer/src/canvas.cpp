#include "canvas.h"

Canvas::Canvas (Image* _pixels, const Rect& _trappings)
: AbstractWindow (_trappings), canvas_pixels (_pixels) {}


