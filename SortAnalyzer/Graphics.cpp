#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "../MyLib/my_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include "Primitives.h"

//#define DEBUG
#include "../MyLib/debug_info.h"

// https://www.glfw.org/docs/3.0/quick.html


static void error_callback (int error, const char* description);
static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
void GraphicsMainLoop (GLFWwindow* window);


int main  (void)
{
        GLFWwindow* window;
        glfwSetErrorCallback (error_callback);
        
        if  (!glfwInit ()) exit (EXIT_FAILURE);
        
        window = glfwCreateWindow (1200, 675, "Simple example", NULL, NULL);
        
        if  (!window) {
                glfwTerminate ();
                exit (EXIT_FAILURE);
        }

        glfwMakeContextCurrent (window);
        glfwSetKeyCallback (window, key_callback);
        GraphicsMainLoop (window);

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
        Vector<Vector<size_t>> result = CompGraph_of_sort (MergeSortRecursive<MyType>);
        Vector <Point2d> points (result.size ());
        for (int i = 0; i < result.size (); ++i) {
                points[i].x = result[i][0];
                points[i].y = result[i][1];
        }
        DEB_INFO
        CoordinatePlane graph_of_assigns (0.5, 1.0, Point2d (-1.0, 0.0));


        Vector<Vector<size_t>> result2 = CompGraph_of_sort (BubbleSort<MyType>);
        Vector <Point2d> points2 (result2.size ());
        for (int i = 0; i < result2.size (); ++i) {
                points2[i].x = result2[i][0];
                points2[i].y = result2[i][1];
        }
        graph_of_assigns.add_graph_by_p_arr (points);
        graph_of_assigns.add_graph_by_p_arr (points2);
        

        Button<SortDrawFunctor<Numeric<int>>> but (graph_of_assigns, BubbleSort<MyType>);
        but.action ();

        DEB_INFO
        //CoordinatePlane graph_of_assigns_2 (1.0, 1.0, Point2d (0.0, 0.0), points);
        //printf ("Hello 3\n");
        while  (!glfwWindowShouldClose (window)) {

                //DrawGraphByVertex (result);
                glClear (GL_COLOR_BUFFER_BIT);
                DEB_INFO
                graph_of_assigns.draw ();
                DEB_INFO
                //graph_of_assigns_2.draw ();
                
                
                glfwSwapBuffers (window);
                DEB_INFO
                glfwPollEvents ();
                DEB_INFO
        }

}