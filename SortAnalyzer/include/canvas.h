#ifndef CANVAS_H
#define CANVAS_H
#include "image.h"
#include "window.h"

class Canvas : public AbstractWindow {
    Image* canvas_pixels;

public:

    Canvas (Image* _pixels, const Rect& _trappings);
    Point2d convertToCanvasCoords (const Point2d& screen_coords);
   // bool is

    void draw () const override;
};


#endif // CANVAS_H