#include "tools.h"
#include "tool_manager.h"
#include <assert.h>


void Pencil::drawSquare (Canvas* canvas, double center_x, double center_y, int a, const Pixel& pixel) {
    assert (center_y > 0);
    assert (center_x > 0);
    assert (canvas);
    assert (a > 0);

    for (int y = center_y - a / 2; y <= center_y + a / 2; ++y) {
        for (int x = center_x - a / 2; x <= center_x + a / 2; ++x) {
            printf ("suare x,y = %d, %d", x, y);
            canvas->setPixel (x, y, pixel);
        }
    }
}

void Pencil::apply (Canvas* canvas, double x, double y) {
    assert (x > 0);
    assert (y > 0);
    assert (canvas);


    printf ("Применяюсь по координатам x = %lf, y = %lf\n", x, y);
    canvas->setPixel (x, y, Pixel (COLORS::BLACK));

    if (last_apply_coords.x < 0) {
        last_apply_coords = {x, y};
    }
    
    ab::Pixel cur_pxl (ToolManager::getAcitveColor ());
    int thickness = ToolManager::getThickness ();
    printf ("x,y = %lf, %lf\n", x, y);
    drawSquare (canvas, x, y, thickness, cur_pxl);

}
