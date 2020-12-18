#ifndef VIEW_PORT_H
#define VIEW_PORT_H

#include "color.h"

struct ViewPort {
    int off_x  = 0;
    int off_y  = 0;
    int width  = 0;
    int height = 0;

    ViewPort () = default;

    void setSizeByRect (const ab::Rect& rect);
};


#endif // VIEW_PORT_H