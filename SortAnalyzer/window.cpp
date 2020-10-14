#include "window.h"



void SortAnalyzer::run () {
    if (!event_queue.empty ()) {
        windows.HandleEvent (event_queue.front().get ());
        event_queue.pop ();
    }
}


void SortAnalyzer::MouseClickCallback (GLFWwindow* window, int button, int action, int mods) {
    double x_pos (0), y_pos (0);
    glfwGetCursorPos (window, &x_pos, &y_pos);
    std::unique_ptr<MouseClickEvent> event (new MouseClickEvent (x_pos, y_pos, button, action, mods));
    event_queue.push (std::move (event));
}



bool AbstractWindowContainer::HandleEvent (AbstractEvent* event) {
    bool is_consumed = false;
     

    if (event->coordinatble) {
        CoordinatbleEvent* temp_event = static_cast<CoordinatbleEvent*> (event);
        is_consumed = CheckCoordinate (temp_event->pos_x, temp_event->pos_y);
        if (!is_consumed) return false;
    }

    for (auto window : subwindows) {
        is_consumed = window->HandleEvent (event);
        if (is_consumed) return true;
    }

    switch (event->type)
    {
    case MOUSE_CLICK:
        onMouseClick (dynamic_cast<MouseClickEvent*> (event));
        break;
    
    }

    return true;
}



QuadWindow::QuadWindow (double _x, double _y, double _x_size, double _y_size)
: x (_x), y (_y), size_x (_x_size), size_y (_y_size) {}



bool QuadWindow::CheckCoordinate (double pos_x, double pos_y) const {
    return pos_x > x && pos_y < y && pos_x < x + size_x && pos_y > y - size_y? true : false;
}

bool AbstractWindow::HandleEvent (AbstractEvent* event) {
    bool is_consumed = false;
     

    if (event->coordinatble) {
        CoordinatbleEvent* temp_event = dynamic_cast<CoordinatbleEvent*> (event);
        is_consumed = CheckCoordinate (temp_event->pos_x, temp_event->pos_y);
        if (!is_consumed) return false;
    }

    switch (event->type)
    {
    case MOUSE_CLICK:
        onMouseClick (dynamic_cast<MouseClickEvent*> (event));
        break;
    }

    return true;

}