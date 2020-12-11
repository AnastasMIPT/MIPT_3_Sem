#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "debug_info.h"
#include "config.h"
#include "application.h"
#include "label.h"
#include "image_pool.h"

template <>
GSystem GEngine::system;

void GraphicsMainLoop ();

int main  (void)
{
 
    AbstractScrollableWindow scroll_w (50, 30);
    ScrollBar s_bar (&scroll_w, {0.975, 0.0, 0.02, 1.0, ab::COLORS::LIGHT_GRAY});

    Application::addObject (&s_bar);
 

 
    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();  
    }
}

