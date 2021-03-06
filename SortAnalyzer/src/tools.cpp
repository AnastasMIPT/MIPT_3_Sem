#include "tools.h"
#include "tool_manager.h"
#include <assert.h>
#include <algorithm>
#include <cmath>

void Eraser::startApplying (Canvas* canvas, double x, double y) {
    printf ("Я ластик, я начал применяться\n");
    last_apply_coords = {-1, -1};
}


void Eraser::apply (Canvas* canvas, double x, double y) {
    size_t thickness = ToolManager::getThickness ();
    
    if (x - thickness / 2 < 0 || y - thickness / 2 < 0) return;
    assert (x > 0);
    assert (y > 0);
    assert (canvas);


    printf ("Применяюсь по координатам x = %lf, y = %lf\n", x, y);
    
    if (last_apply_coords.x < 0) {
        last_apply_coords = {x, y};
    }
    
    ab::Pixel cur_pxl (COLORS::WHITE);
    canvas->drawLine (last_apply_coords, {x, y}, cur_pxl, thickness);
    

    last_apply_coords = {x, y};
}

void Eraser::finishApplying (Canvas* canvas, double x, double y) {
    printf ("Я ластик, я закончил применяться\n");
    last_apply_coords = {-1, -1};
}


void Pencil::startApplying (Canvas* canvas, double x, double y) {
    printf ("Я карандаш, я начал применяться\n");
    last_apply_coords = {-1, -1};
}


void Pencil::apply (Canvas* canvas, double x, double y) {
    size_t thickness = ToolManager::getThickness ();
    
    if (x - thickness / 2 < 0 || y - thickness / 2 < 0) return;
    assert (x > 0);
    assert (y > 0);
    assert (canvas);


    printf ("Применяюсь по координатам x = %lf, y = %lf\n", x, y);
    
    if (last_apply_coords.x < 0) {
        last_apply_coords = {x, y};
    }
    
    ab::Pixel cur_pxl (ToolManager::getAcitveColor ());
    canvas->drawLine (last_apply_coords, {x, y}, cur_pxl, thickness);
    

    last_apply_coords = {x, y};
}

void Pencil::finishApplying (Canvas* canvas, double x, double y) {
    printf ("Я карандаш, я закончил применяться\n");
    last_apply_coords = {-1, -1};
}