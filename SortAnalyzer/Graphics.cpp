#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "../MyLib/my_vector.h"
#include "Sorts.h"
#include "../MyLib/MyInteger.h"
#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"

#include "button.h"
#include "window.h"
//#define DEBUG
#include "../MyLib/debug_info.h"

// https://www.glfw.org/docs/3.0/quick.html



using MyType = Numeric<int>;

template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;

AbstractWindowContainer AbstractApplication::windows;
std::queue <std::unique_ptr<AbstractEvent>> AbstractApplication::event_queue;
AbstractWindowContainer::WindowList AbstractWindowContainer::subwindows;


Vector<MyType> rand_vector (size_t size);

template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size = 10, size_t delta = 10, size_t max_size = 100);



void GraphicsMainLoop (GLFWwindow* window, SortAnalyzer& app);

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
    GraphicsMainLoop (app.app_window, app);
}

void GraphicsMainLoop (GLFWwindow* window, SortAnalyzer& app) {

    while  (!glfwWindowShouldClose (window)) {

        glClear (GL_COLOR_BUFFER_BIT);
        app.drawObjects ();

        glfwSwapBuffers (window);
        glfwPollEvents ();
        app.run ();
    }

}




template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size, size_t delta, size_t max_size) {
    size_t size = start_size;
    Vector<Vector<size_t>> result;
    while (size <= max_size)
    {
        Vector<MyType> arr (rand_vector (size));

        func_sort (&arr[0], 0, size);

        Vector<size_t> temp (3);
        temp[0] = size;
        temp[1] = MyType::num_of_comp ();
        temp[2] = MyType::num_of_assigns ();
        result.push_back (temp);
        
        MyType::num_of_comp_to_zero ();
        MyType::num_of_assigns_to_zero ();
        
        size += delta;
    }
    
    return result;
}



Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = rand () % 1024;
    }
    return vec;
}
