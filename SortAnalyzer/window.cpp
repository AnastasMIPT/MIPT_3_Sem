#include "window.h"

void Application::pollEvent () {
    if (!event_queue.empty ()) {
        Event* event = event_queue.front ().get ();
        bool is_consumed = false;
        switch (event->type)
        {
        case Event::EventTypes::MOUSE_CLICK:
            is_consumed = windows.onMouseClick (event->ev.mouse_click);
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

void AbstractApplication::drawObjects () const {
    for (auto window : windows) {
        window->draw ();
    }
}

void WindowContainer::addWindow (IWindow* window) {
    subwindows.push_back (window);
}


bool WindowContainer::onMouseClick (const MouseClickEvent& event) {
    printf ("Принял событие\n");

    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false;
  
    printf ("у события нужные координаты\n");
    for (auto window : subwindows) {
        is_consumed = window->onMouseClick (event);
        if (is_consumed) return true;
    }
    printf ("событие не поглащено\n");


}
