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

std::queue <std::unique_ptr<Event>> AbstractApplication::event_queue;
IWindow* AbstractApplication::active_window = NULL;

template <>
GSystem GEngine::system;


WindowContainer AbstractApplication::windows ({0.0, 0.0, 1.0, 1.0, COLORS::DEFAULT_BACKGROUND});



void GraphicsMainLoop ();

int main  (void)
{
    std::unique_ptr<AbstractScrollableWindow> scroll_w (
        new AbstractScrollableWindow (50, 30)
    );    
        
    std::unique_ptr<ScrollBar> s_bar (
        new ScrollBar (scroll_w.get (), {0.975, 0.0, 0.02, 1.0, ab::COLORS::LIGHT_GRAY})
    );

    // std::unique_ptr<LabelWindow> label (
    //     new LabelWindow ("\tanastas", {0.1, 0.1, 0.4, 0.3, ab::COLORS::BLUE})
    // );

    Application::addObject (s_bar.get ());
    //Application::addObject (label.get ());

    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    Image my_img = GEngine::system.loadImageFromFile ("./resources/images/kotik.jpg");
    printf ("height = %lu\n", my_img.getHeight ());
    for (int i = 0; i < 10; i++) {
        auto pixel = my_img.getPixel (i, 0);
        printf ("r= %d, g = %d, b = %d, a = %d\n", pixel.red, pixel.green, pixel.blue, pixel.alpha);
    }
    //GEngine::system.drawImage ({0.1, 0.1, 0.4, 0.3}, my_img);
        
    while  (!Application::shouldCLose ()) {
        GEngine::system.drawImage ({0.1, 0.1, 0.4, 0.3}, my_img);
        Application::run ();
    
    }
}

