#include "events.h"

Event::Event (const MouseClickEvent& _mouse_click) : type (MOUSE_CLICK) {
    ev.mouse_click = _mouse_click;
}


Event::Event (const MouseMoveEvent& _mouse_move) : type (MOUSE_MOVE) {
    ev.mouse_move = _mouse_move;
}

Event::Event () : type (DEFAULT_EVENT) {}