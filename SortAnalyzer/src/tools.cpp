#include "tools.h"
#include "tool_manager.h"
#include <assert.h>
#include <algorithm>
#include <cmath>

void Pencil::drawSquare (Canvas* canvas, double center_x, double center_y, int a, const Pixel& pixel) {
    assert (center_y > 0);
    assert (center_x > 0);
    assert (canvas);
    assert (a > 0);

    for (int y = center_y - a / 2; y <= center_y + a / 2; ++y) {
        for (int x = center_x - a / 2; x <= center_x + a / 2; ++x) {
            canvas->setPixel (x, y, pixel);
        }
    }
}

void Pencil::startApplying () {
    printf ("Я карандаш, я начал применяться\n");
    last_apply_coords = {-1, -1};
}


void Pencil::apply (Canvas* canvas, double x, double y) {
    assert (x > 0);
    assert (y > 0);
    assert (canvas);


    printf ("Применяюсь по координатам x = %lf, y = %lf\n", x, y);
    
    if (last_apply_coords.x < 0) {
        last_apply_coords = {x, y};
    }
    
    ab::Pixel cur_pxl (ToolManager::getAcitveColor ());
    int thickness = ToolManager::getThickness ();
    
    Point2d lst = last_apply_coords;
    if (std::abs (x - lst.x) > std::abs (y - lst.y)) {
        for (int t = std::min (lst.x, x); t < std::max (x, lst.x); ++t) {
            double y_t = (t - lst.x) * (y - lst.y) / (x - lst.x) + lst.y; // calc y_t by t
            drawSquare (canvas, t, y_t, thickness, cur_pxl);
        }
    } else {
        for (int t_y = std::min (lst.y, y); t_y < std::max (y, lst.y); ++t_y) {
            double t = (t_y - lst.y) * (x - lst.x) / (y - lst.y) + lst.x; // calc y_t by t
            drawSquare (canvas, t, t_y, thickness, cur_pxl);
        }
    }

    

    last_apply_coords = {x, y};
}

void Pencil::finishApplying () {
    printf ("Я карандаш, я закончил применяться\n");
    last_apply_coords = {-1, -1};
}