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

template <>
GSystem GEngine::system;

void GraphicsMainLoop ();

int main  (void)
{

    Application::loadDefaultImages ();

    AbstractScrollableWindow scroll_w (50, 30);
    ScrollBar s_bar (&scroll_w, {0.975, 0.0, 0.02, 1.0, ab::COLORS::LIGHT_GRAY});

    //Image my_img = GEngine::system.loadImageFromFile ("./resources/images/pencil.png");
    
    Button<ToolFunctor> im_but ({0.1, 0.1, 0.025, 0.05, COLORS::TRANSPARENT}, TOOLS::PENCIL);
    im_but.setImage (ImagePool::getImageById (DEF_IMAGES::PENCIL));

    Application::addObject (&s_bar);
    Application::addObject (&im_but);
 


    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();  
    }
}

