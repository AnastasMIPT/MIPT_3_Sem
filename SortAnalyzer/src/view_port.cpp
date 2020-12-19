#include "view_port.h"



void ViewPort::setSizeByRect (const ab::Rect& rect) {
    width  = rect.width;
    height = rect.height;
}