#include "canvas.h"
#include "assert.h"

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


void Canvas::drawSquare (double center_x, double center_y, int a, const Pixel& pixel) {
    assert (center_y > 0);
    assert (center_x > 0);
    assert (a > 0);

    for (int y = center_y - a / 2; y <= center_y + a / 2; ++y) {
        for (int x = center_x - a / 2; x <= center_x + a / 2; ++x) {
            setPixel (x, y, pixel);
        }
    }
}

void Canvas::drawLine (Point2d p1, Point2d p2, const Pixel& pixel, int thickness) {
    if (std::abs (p2.x - p1.x) > std::abs (p2.y - p1.y)) {
        for (int t = std::min (p1.x, p2.x); t < std::max (p2.x, p1.x); ++t) {
            double y_t = (t - p1.x) * (p2.y - p1.y) / (p2.x - p1.x) + p1.y; // calc y_t by t
            drawSquare (t, y_t, thickness, pixel);
        }
    } else {
        for (int t_y = std::min (p1.y, p2.y); t_y < std::max (p2.y, p1.y); ++t_y) {
            double t = (t_y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x; // calc y_t by t
            drawSquare (t, t_y, thickness, pixel);
        }
    }
}



double Canvas::getRatio (bool is_vertical) {
    if (is_vertical) {
        return view.height / (double) canvas_pixels->getHeight ();
    } else {
        return view.width  / (double) canvas_pixels->getWidth ();
    }
    
}


void Canvas::scrollOnceUp (bool is_vertical) {
    if (is_vertical) {
        if (view.off_y - 1 > 0) view.off_y--;
    } else {
        if (view.off_x + view.width + 1 < canvas_pixels->getWidth ())
            view.off_x++;
    }
}


void Canvas::scrollOnceDown (bool is_vertical) {
    if (is_vertical) {
        if (view.off_y + 1 + view.height< canvas_pixels->getHeight ()) view.off_y++;
    } else {
        if (view.off_x - 1 > 0)
            view.off_x--;
    }
}

void Canvas::slideByRatio (double ratio, bool is_vertical) {
    if (is_vertical) {
        view.off_y = ratio * (canvas_pixels->getHeight () - view.height);
    } else {
        view.off_x = ratio * (canvas_pixels->getWidth () - view.width);
    }
}