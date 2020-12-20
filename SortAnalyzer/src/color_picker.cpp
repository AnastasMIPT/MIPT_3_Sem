#include "color_picker.h"
#include "tool_manager.h"

ColorPicker::ColorPicker (const Rect& _tr, SlidableColor* _color)
: WindowContainer (_tr), color (_color),
  color_disp ({_tr.coords.x + off, _tr.coords.y + off,
               _tr.width * disp_col_rat,_tr.height - 2 * off,
               _color->getColor ()}),
  red   ({_tr.coords.x + 2 * off + _tr.width * disp_col_rat,
          _tr.coords.y + _tr.height - off - (_tr.height - 5 * off) / 3/*4*/,
          _tr.width - 3 * off - color_disp.trappings.width, 
            (_tr.height - 5 * off) / 3/*4*/, _tr.color}, &_color->r, COLORS::RED),
  
  
  green ({red.trappings.coords.x, red.trappings.coords.y - off - red.trappings.height,
          red.trappings.width, red.trappings.height, _tr.color}, &_color->g, COLORS::GREEN),
  
  blue  ({red.trappings.coords.x, green.trappings.coords.y - off - red.trappings.height,
          red.trappings.width, red.trappings.height, _tr.color}, &_color->b, COLORS::BLUE)
  
 /* alpha ({red.trappings.coords.x, blue.trappings.coords.y - off - red.trappings.height,
          red.trappings.width, red.trappings.height, _tr.color},
          &_color->a, COLORS::TRANSPARENT)*/ {

    subwindows.push_back (&color_disp);
    subwindows.push_back (&red);
    subwindows.push_back (&green);
    subwindows.push_back (&blue);
//    subwindows.push_back (&alpha);
}


bool ColorPicker::onMouseClick (const MouseClickEvent& event) {
    WindowContainer::onMouseClick (event);
    if (WindowContainer::CheckCoordinate (event.pos_x, event.pos_y)) {
        color_disp.trappings.color = ToolManager::getAcitveColor ();
    }
}