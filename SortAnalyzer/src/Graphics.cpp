#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "../../MyLib/debug_info.h"
#include "config.h"

WindowContainer AbstractApplication::windows (-1.0, -1.0, 2.0, 2.0, {0, 1, 0.5});
std::queue <std::unique_ptr<Event>> AbstractApplication::event_queue;
IWindow* AbstractApplication::active_window = NULL;

template <>
GSystem GEngine::system;

void GraphicsMainLoop ();

int main  (void)
{
   
    std::unique_ptr<ScrollBar> s_bar (new ScrollBar (0.95, -1.0, 0.05, 2.0, {0.9, 0.9, 0.9}));
    Application::addObject (s_bar.get ());
    GraphicsMainLoop ();
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();
    }
}

