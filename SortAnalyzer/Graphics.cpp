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


WindowContainer AbstractApplication::windows;
std::queue <std::unique_ptr<Event>> AbstractApplication::event_queue;
WindowContainer::WindowList WindowContainer::subwindows;


void GraphicsMainLoop (SortAnalyzer& app);

int main  (void)
{
    SortAnalyzer app (1200, 675, "SortAnalyzer");
    
    std::unique_ptr<CoordinatePlane> graph_of_assigns (new CoordinatePlane (-1.0, 0.0, 1.0, 1.0)); 
    std::unique_ptr<CoordinatePlane> graph_of_comp (new CoordinatePlane (0.0, 0.0,1.0, 1.0)); 
    std::unique_ptr<Button<SortDrawFunctor<Numeric<int>>>> bubble_but (new Button<SortDrawFunctor<Numeric<int>>> (-0.5, -0.5, 0.3, 0.3, 
    Color (1.0, 0.0, 0.0), graph_of_assigns.get (), graph_of_comp.get (), BubbleSort<MyType>));

    std::unique_ptr<Button<SortDrawFunctor<Numeric<int>>>> merge_but (new Button<SortDrawFunctor<Numeric<int>>> (0.5, -0.5, 0.3, 0.3, 
    Color (0.0, 1.0, 0.0), graph_of_assigns.get (), graph_of_comp.get (), MergeSortRecursive<MyType>));

    // std::unique_ptr<QuadWindow> arrow_up (new QuadWindow (0.7, 0, 0.1, 0.200));
    // std::unique_ptr<QuadWindow> arrow_down (new QuadWindow (0.7, 0.8, 0.1, 0.200));
    // std::unique_ptr<QuadWindow> scroll_bar (new QuadWindow (0.7, 0.25, 0.1, 0.500));
    //std::unique_ptr<QuadWindow> slider (new QuadWindow (0.7, 0, 0.2, 0.200));

    app.addObject (bubble_but.get ());
    app.addObject (merge_but.get ());
    app.addObject (graph_of_assigns.get ());
    app.addObject (graph_of_comp.get ());
    // app.addObject (arrow_up.get ());
    // app.addObject (arrow_down.get ());
    // app.addObject (scroll_bar.get ());
    //app.addObject (slider.get ());
    GraphicsMainLoop (app);
}

void GraphicsMainLoop (SortAnalyzer& app) {

    while  (!app.shouldCLose ()) {
        glClear (GL_COLOR_BUFFER_BIT);
        app.run ();
    }

}

