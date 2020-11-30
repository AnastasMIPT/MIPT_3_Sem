#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "../../MyLib/debug_info.h"
#include "config.h"
#include "application.h"

std::queue <std::unique_ptr<Event>> AbstractApplication::event_queue;
IWindow* AbstractApplication::active_window = NULL;

template <>
GSystem GEngine::system;

WindowContainer AbstractApplication::windows ({0.0, 0.0, 1.0, 1.0, COLORS::DEFAULT_BACKGROUND});



void GraphicsMainLoop ();

int main  (void)
{
    std::unique_ptr<AbstractScrollableWindow> scroll_w (new AbstractScrollableWindow (50, 30));    
    std::unique_ptr<ScrollBar> s_bar (new ScrollBar (scroll_w.get (), {0.975, 0.0, 0.025, 1.0, ab::COLORS::LIGHT_GRAY}));


    Application::addObject (s_bar.get ());

    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();
    }
}

