#include "application.h"


void AbstractApplication::pollEvent () {
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
                printf ("передал mouse_move активному окну, y = %lf\n", event->ev.mouse_move.pos_y);
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

void AbstractApplication::run () {
    GEngine::system.clear ();
    
    drawObjects ();
    
    std::unique_ptr<Event> event = std::move (GEngine::system.pollEvent ());
    if (event->type != Event::EventTypes::DEFAULT_EVENT) event_queue.push (std::move (event));
    pollEvent ();
}

bool AbstractApplication::shouldCLose () {
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

void Application::loadDefaultImages () {
    ImagePool::loadDefaultImages ();
}