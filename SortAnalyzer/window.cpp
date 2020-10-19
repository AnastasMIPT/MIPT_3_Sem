#include "window.h"



void SortAnalyzer::run () {
    if (!event_queue.empty ()) {
        if (windows.HandleEvent (event_queue.front ().get ())) printf ("Событие обработано\n");
        event_queue.pop ();
    }
}


void SortAnalyzer::MouseClickCallback (GLFWwindow* window, int button, int action, int mods) {
    double x_pos (0), y_pos (0);
    glfwGetCursorPos (window, &x_pos, &y_pos);
    int width, height;
    glfwGetWindowSize (window, &width, &height);

    x_pos = x_pos * 2 / width  - 1;
    y_pos = -(y_pos * 2 / height - 1);

    std::unique_ptr<MouseClickEvent> event (new MouseClickEvent (x_pos, y_pos, button, action, mods));
    event_queue.push (std::move (event));
    printf ("Пойман щелчок мыши\n");
}

void AbstractApplication::addObject (AbstractWindow* window) {
    windows.addWindow (window);
}

void AbstractApplication::drawObjects () const {
    for (auto window : windows) {
        window->draw ();
    }
}

void AbstractWindowContainer::addWindow (AbstractWindow* window) {
    subwindows.push_back (window);
}


bool AbstractWindowContainer::HandleEvent (AbstractEvent* event) {
    bool is_consumed = false;
    printf ("Принял событие\n");

    if (event->is_coordinatble) {
        CoordinatbleEvent* temp_event = static_cast<CoordinatbleEvent*> (event);
        is_consumed = CheckCoordinate (temp_event->pos_x, temp_event->pos_y);
        if (!is_consumed) return false;
    }

    printf ("у события нужные координаты\n");
    for (auto window : subwindows) {
        is_consumed = window->HandleEvent (event);
        if (is_consumed) return true;
    }
    printf ("событие не поглащено\n");
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
    printf ("Проверяю координаты входящие: %lf, %lf. Координаты кнопки %lf, %lf размеы: %lf, %lf\n",
    pos_x, pos_y, x, y, size_x, size_y);
   if (!((pos_x > x) && (pos_y > y) && (pos_x < x + size_x) && (pos_y < y + size_y))) printf ("Координаты не подходят\n");
    return pos_x > x && pos_y > y && pos_x < x + size_x && pos_y < y + size_y? true : false;
}

bool AbstractWindow::HandleEvent (AbstractEvent* event) {
    bool is_consumed = false;
     
    printf ("пытаюсь поглатить\n");
    if (event->is_coordinatble) {
        CoordinatbleEvent* temp_event = dynamic_cast<CoordinatbleEvent*> (event);
        is_consumed = CheckCoordinate (temp_event->pos_x, temp_event->pos_y);
        if (!is_consumed) return false;
    }
    printf ("поглатил\n");
    switch (event->type)
    {
    case MOUSE_CLICK:
        printf ("Запустил onMouseClick\n");
        onMouseClick (dynamic_cast<MouseClickEvent*> (event));
        break;
    }

    return true;

}