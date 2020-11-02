
#define DEBUG
#include "../../MyLib/debug_info.h"
#include "window.h"



void Application::pollEvent () {
    if (!event_queue.empty ()) {
        Event* event = event_queue.front ().get ();
        bool is_consumed = false;
        switch (event->type)
        {
        case Event::EventTypes::MOUSE_CLICK:
            if (active_window != NULL) {
                active_window->onMouseClick (event->ev.mouse_click);
            } else
                is_consumed = windows.onMouseClick (event->ev.mouse_click);
            break;
        case Event::EventTypes::MOUSE_MOVE:
            if (active_window != NULL) {
                active_window->onMouseMove (event->ev.mouse_move);
            }
            break;
        default:
            printf ("неизвестный тип события\n");
        }
        if (is_consumed) printf ("Событие обработано\n");
        event_queue.pop ();
    }
}

void Application::run () {
    glClear (GL_COLOR_BUFFER_BIT);
    drawObjects ();
    std::unique_ptr<Event> event = std::move (GEngine::system.pollEvent ());
    if (event->type != Event::EventTypes::DEFAULT_EVENT) event_queue.push (std::move (event));
    pollEvent ();
}

bool Application::shouldCLose () {
    return GEngine::system.shouldClose ();
}


void AbstractApplication::addObject (IWindow* window) {
    windows.addWindow (window);
}

void AbstractApplication::drawObjects () {
    windows.draw ();
}

void AbstractApplication::setActiveWindow (IWindow* window) {
    active_window = window;
}

void WindowContainer::addWindow (IWindow* window) {
    subwindows.push_back (window);
}

void WindowContainer::draw () const {
    GEngine::system.drawRect ({{x, y}, size_x, size_y, color});
    for (auto window : subwindows) {
        window->draw ();
    }
}

bool WindowContainer::onMouseClick (const MouseClickEvent& event) {
    printf ("Принял событие\n");
    DEB_INFO
    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    printf ("is_consumed = %d\n", is_consumed);
    if (!is_consumed) {
        printf ("у события неверные координаты: %lf, %lf\n", event.pos_x, event.pos_y);
        printf ("Координаты контейнера %lf, %lf, размеры: %lf, %lf\n", x, y, size_x, size_y);
        return false;
    }
    DEB_INFO
    printf ("у события нужные координаты\n");
    printf ("Координаты контейнера %lf, %lf\n", x, y);
    for (auto window : subwindows) {
        is_consumed = window->onMouseClick (event);
        if (is_consumed) printf ("Приянло подокно с координатами y = %lf\n", dynamic_cast<QuadWindow*> (window)->y);
        if (is_consumed) return true;
    }

    printf ("событие не поглащено\n");

    return false;
}


WindowContainer::WindowContainer (double _x, double _y, double _x_size, double _y_size, const Color& _color)
: QuadWindow (_x, _y, _x_size, _y_size, _color) {}

QuadWindow::QuadWindow (double _x, double _y, double _x_size, double _y_size, const Color& _color)
: x (_x), y (_y), size_x (_x_size), size_y (_y_size), color (_color) {}

void QuadWindow::draw () const {
    GEngine::system.drawRect ({{x, y}, size_x, size_y, color});
}

bool QuadWindow::CheckCoordinate (double pos_x, double pos_y) const {
    printf ("Проверяю координаты входящие: %lf, %lf. Координаты кнопки %lf, %lf размеы: %lf, %lf\n",
    pos_x, pos_y, x, y, size_x, size_y);
    fflush (stdin);
    if (!((pos_x > x) && (pos_y > y) && (pos_x < x + size_x) && (pos_y < y + size_y))) printf ("Координаты не подходят\n");
    return pos_x > x && pos_y > y && pos_x < x + size_x && pos_y < y + size_y? true : false;
}

bool QuadWindow::onMouseClick (const MouseClickEvent& event) {
    DEB_INFO
    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false;
    DEB_INFO
    printf ("Я квадратное окно, на меня нажали, мои координаты: %lf, %lf, col_r = %lf, col_g = %lf, col_b = %lf\n", x, y, color.red, color.green, color.blue);
    return true;
}


bool AbstractDragableWindow::onMouseClick (const MouseClickEvent& event) {
    DEB_INFO
    if (event.button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == event.action && CheckCoordinate (event.pos_x, event.pos_y)) {
            is_drag = true;
            Application::setActiveWindow (this); 
        }
        else if (GLFW_RELEASE == event.action) {
            DEB_INFO
            is_drag = false;
            Application::setActiveWindow (NULL);
        }
    }
}

void AbstractDragableWindow::onMouseMove (const MouseMoveEvent& event) {
    DEB_INFO
    move (event.pos_x, event.pos_y);
}
