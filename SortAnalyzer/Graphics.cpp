#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "../MyLib/my_vector.h"
#include "Primitives.h"
#include "button.h"
#include "window.h"
//#define DEBUG
#include "../MyLib/debug_info.h"


AbstractWindowContainer AbstractApplication::windows;
std::queue <std::unique_ptr<AbstractEvent>> AbstractApplication::event_queue;
AbstractWindowContainer::WindowList AbstractWindowContainer::subwindows;


void GraphicsMainLoop (SortAnalyzer& app);

int main  (void)
{
    SortAnalyzer app (1200, 675, "SortAnalyzer");
    
    std::unique_ptr<CoordinatePlane> graph_of_assigns (new CoordinatePlane (-1.0, 0.0, 1.0, 1.0)); 
    std::unique_ptr<CoordinatePlane> graph_of_comp (new CoordinatePlane (0.0, 0.0,1.0, 1.0)); 
    std::unique_ptr<Button<SortDrawFunctor<Numeric<int>>>> butt (new Button<SortDrawFunctor<Numeric<int>>> (-0.5, -0.5, 0.3, 0.3, 
    Color (1.0, 0.0, 0.0), graph_of_assigns.get (), graph_of_comp.get (), BubbleSort<MyType>));

    app.addObject (butt.get ());
    app.addObject (graph_of_assigns.get ());
    app.addObject (graph_of_comp.get ());
    GraphicsMainLoop (app);
}

void GraphicsMainLoop (SortAnalyzer& app) {

    while  (!app.shouldCLose ()) {
        glClear (GL_COLOR_BUFFER_BIT);
        app.run ();
    }

}

