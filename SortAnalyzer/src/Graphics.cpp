#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "../../MyLib/debug_info.h"
#include "config.h"

WindowContainer AbstractApplication::windows ({-1.0, -1.0, 2.0, 2.0, {0, 1, 0.5}});
//WindowContainer AbstractApplication::windows ({0.0, 675, 600.0, 675.0, {0, 1, 0.5}});

std::queue <std::unique_ptr<Event>> AbstractApplication::event_queue;
IWindow* AbstractApplication::active_window = NULL;

template <>
GSystem GEngine::system;

void GraphicsMainLoop ();

int main  (void)
{
    std::unique_ptr<AbstractScrollableWindow> scroll_w (new AbstractScrollableWindow (50, 30));
    std::unique_ptr<ScrollBar> s_bar (new ScrollBar (scroll_w.get (), {0.95, -1.0, 0.05, 2.0, {0.9, 0.9, 0.9}}));
    Application::addObject (s_bar.get ());

    // std::unique_ptr<AbstractScrollableWindow> scroll_w (new AbstractScrollableWindow (50, 30));
    // std::unique_ptr<ScrollBar> s_bar (new ScrollBar (scroll_w.get (), {300 + 0.95 * 600 / 2, 675, 0.05 * 600, 675, {0.9, 0.9, 0.9}}));
    // std::unique_ptr<AbstractWindow> wind (new AbstractWindow ({300, 300, 200, 200, {0.8, 0.7, 0.6}}));
    Application::addObject (s_bar.get ());
    //Application::addObject (wind.get());

    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();
    }
}

