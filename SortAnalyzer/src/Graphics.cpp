#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "debug_info.h"
#include "config.h"
#include "application.h"
#include "label.h"
#include "tool_bar.h"
#include "painter.h"
#include "scroll_bar.h"
#include "fader.h"
#include "setting_window.h"

template <>
GSystem GEngine::system;

void GraphicsMainLoop ();

int main  (void)
{

    Application::loadDefaultImages ();
    

    AbstractScrollableWindow scroll_w (50, 5);
    
    AbstractScrollableWindow scroll_w2 (50, 20);
    
    //Image my_img = GEngine::system.loadImageFromFile ("./resources/images/pencil.png");
    
    // Button<ToolFunctor> im_but ({0.1, 0.1, 0.025, 0.05, COLORS::TRANSPARENT}, TOOLS::PENCIL);
    // im_but.setImage (ImagePool::getImageById (DEF_IMAGES::PENCIL));
    size_t im_id = ImagePool::addImage ("./resources/images/kotik.jpg");
    
    ToolBar tool_bar ({0.7, 0.8, 0.2, 0.2, COLORS::DEFAULT_TOOL_BAR});
    
    Image white (1000, 700, Pixel (255, 128, 255, 255));
    
    Canvas canvas (&white, {0.0, 0.04, 0.98, 0.76});
    
    SlidableValue<double> val (0.8, 0.0, 1.0);

    //Fader<double> fad ({0.4, 0.9, 0.2, 0.05, COLORS::DEFAULT_BACKGROUND}, &val, COLORS::DEFAULT_BUTTON);

    SettingWindow<size_t> thickness_w ({0.4, 0.8, 0.2, 0.2, COLORS::DEFAULT_BACKGROUND},
            ToolManager::getSlidableThick (), "Thickness");

    ScrollBar s_bar (&canvas, {0.98, 0.04, 0.02, 0.76, ab::COLORS::LIGHT_GRAY});
    ScrollBar s_bar2 (&canvas, {0.0, 0.0, 0.98, 0.04, ab::COLORS::LIGHT_GRAY});


    //assert (ImagePool::getImageById (im_id));
    canvas.setImage (ImagePool::getImageById (im_id));

    Painter painter (&canvas, &tool_bar);



    Application::addObject (&s_bar);
    Application::addObject (&painter);
    Application::addObject (&s_bar2);
    Application::addObject (&thickness_w);
    // Application::addObject (&tool_bar);
    // Application::addObject (&canvas);
    


    GraphicsMainLoop ();

    return 0;
}

void GraphicsMainLoop () {
    while  (!Application::shouldCLose ()) {
        Application::run ();  
    }
}

