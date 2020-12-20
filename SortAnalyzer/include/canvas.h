#ifndef CANVAS_H
#define CANVAS_H
#include "image.h"
#include "window.h"
#include "view_port.h"
#include "scrollable_windows.h"

class Canvas : public AbstractWindow, public IScrollableWindow {
    Image* canvas_pixels;
    ViewPort view;

public:

    Canvas (Image* _pixels, const Rect& _trappings);
    Point2d convertToCanvasCoords (const Point2d& screen_coords);

    void setImage (Image* image);
    void setPixel (size_t x, size_t y, const Pixel& pixel);
    void drawSquare (double center_x, double center_y, size_t a, const Pixel& pixel);
    void drawLine (Point2d p1, Point2d p2, const Pixel& pixel, size_t thickness);

    double getRatio (bool is_vertical) override;
    void scrollOnceUp    (bool is_vertical) override;
    void scrollOnceDown  (bool is_vertical) override;
    void slideByRatio   (double retio, bool is_vertical) override;

   // bool is

    void draw () const override;
};


#endif // CANVAS_H