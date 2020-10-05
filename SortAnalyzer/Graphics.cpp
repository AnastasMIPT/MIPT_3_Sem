#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "../MyLib/my_vector.h"
#include "Sorts.h"
#include "../MyLib/MyInteger.h"
#include <stdlib.h>
#include <stdio.h>

#include "Primitives.h"

//#define DEBUG
#include "../MyLib/debug_info.h"

// https://www.glfw.org/docs/3.0/quick.html



using MyType = Numeric<int>;

template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;



Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = rand () % 1024;
    }
    return vec;
}


template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size = 10, size_t delta = 10, size_t max_size = 100) {
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




static void error_callback (int error, const char* description);
static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
void GraphicsMainLoop (GLFWwindow* window);


int main  (void)
{
        DEB_INFO
        GLFWwindow* window;
        glfwSetErrorCallback (error_callback);
        
        if  (!glfwInit ()) exit (EXIT_FAILURE);
        
        window = glfwCreateWindow (1200, 675, "Simple example", NULL, NULL);
        DEB_INFO
        if  (!window) {
                glfwTerminate ();
                exit (EXIT_FAILURE);
        }

        glfwMakeContextCurrent (window);
        glfwSetKeyCallback (window, key_callback);
        DEB_INFO
        GraphicsMainLoop (window);
        DEB_INFO
        glfwDestroyWindow (window);
        glfwTerminate ();
        exit (EXIT_SUCCESS);
}

static void error_callback (int error, const char* description)
{
    fputs (description, stderr);
}

static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if  (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);

}



void GraphicsMainLoop (GLFWwindow* window) {
        // Vector<Vector<size_t>> result = CompGraph_of_sort (MergeSortRecursive<MyType>);
        // Vector <Point2d> points (result.size ());
        // for (int i = 0; i < result.size (); ++i) {
        //         points[i].x = result[i][0];
        //         points[i].y = result[i][1];
        // }
        DEB_INFO
        CoordinatePlane graph_of_assigns (1.0, 1.0, Point2d (-1.0, 0.0));
        CoordinatePlane graph_of_comp    (1.0, 1.0, Point2d (0.0, 0.0));
        DEB_INFO

        // Vector<Vector<size_t>> result2 = CompGraph_of_sort (BubbleSort<MyType>);
        // Vector <Point2d> points2 (result2.size ());
        // for (int i = 0; i < result2.size (); ++i) {
        //         points2[i].x = result2[i][0];
        //         points2[i].y = result2[i][1];
        // }
        // graph_of_assigns.add_graph_by_p_arr (points);
        // graph_of_assigns.add_graph_by_p_arr (points2);
        

        Button<SortDrawFunctor<Numeric<int>>> butBub (0.3, 0.3, Point2d (-0.5, -0.5), Color (1.0, 0.0, 0.0), graph_of_assigns, graph_of_comp, BubbleSort<MyType>);
        DEB_INFO
        butBub.action ();
        
        //but.action ();

        DEB_INFO
        //CoordinatePlane graph_of_assigns_2 (1.0, 1.0, Point2d (0.0, 0.0), points);
        //printf ("Hello 3\n");
        while  (!glfwWindowShouldClose (window)) {

                //DrawGraphByVertex (result);
                glClear (GL_COLOR_BUFFER_BIT);
                DEB_INFO
                graph_of_assigns.draw ();
                DEB_INFO
                graph_of_comp.draw ();
                butBub.draw ();
                
                
                glfwSwapBuffers (window);
                DEB_INFO
                glfwPollEvents ();
                DEB_INFO
        }

}

