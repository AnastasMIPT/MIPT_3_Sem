#ifndef CANVAS_H
#define CANVAS_H
#include "image.h"
#include "window.h"
#include "view_port.h"


class Canvas : public AbstractWindow {
    Image* canvas_pixels;
    ViewPort view;

public:

    Canvas (Image* _pixels, const Rect& _trappings);
    Point2d convertToCanvasCoords (const Point2d& screen_coords);

    void setImage (Image* image);
   // bool is

    void draw () const override;
};


#endif // CANVAS_H