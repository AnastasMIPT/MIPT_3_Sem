#include "events.h"

Event::Event (const MouseClickEvent& _mouse_click) : type (MOUSE_CLICK) {
    ev.mouse_click = _mouse_click;
}

Event::Event () : type (DEFAULT_EVENT) {}