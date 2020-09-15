#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "my_vector.h"
#include "Sorts.h"
#include "MyInteger.h"
#include <stdlib.h>
#include <stdio.h>


// https://www.glfw.org/docs/3.0/quick.html



using MyType = Numeric<int>;

template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);


template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;



Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (int i = 0; i < size; ++i) {
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

void DrawGraphByVertex (const Vector<Vector<size_t>>& results) {
        

        glClear (GL_COLOR_BUFFER_BIT);


        glBegin (GL_LINE_STRIP);
        glColor3f (1.0, 1.0, 1.0);
        for (int i = 0; i < results.size (); ++i) {
                glVertex2f (80 + i * results[i][0], 280 + results[i][1]);
        }
    
        glEnd ();
}

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
        while  (!glfwWindowShouldClose (window)) {
                float ratio;
                int width, height;
                glfwGetFramebufferSize (window, &width, &height);
                ratio = width /  (float) height;
                
                glViewport (0, 0, width, height);
                
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D (0, width, 0, height);

                glMatrixMode (GL_MODELVIEW);
                glLoadIdentity ();
                
                
                DrawGraphByVertex (result);

                // glClearColor (1.f, 0.f, 1.f, 0.5f);
                // glClear (GL_COLOR_BUFFER_BIT);
                // glMatrixMode (GL_PROJECTION);
                // glLoadIdentity ();
                // glOrtho (-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
                // glMatrixMode (GL_MODELVIEW);
                // glLoadIdentity ();
                // glRotatef ( (float) glfwGetTime () * 50.f, 0.f, 0.f, 1.f);
                // glBegin (GL_TRIANGLES);
                // glColor3f (1.f, 0.f, 0.f);
                // glVertex3f (-0.6f, -0.4f, 0.f);
                // glColor3f (0.f, 1.f, 0.f);
                // glVertex3f (0.6f, -0.4f, 0.f);
                // glColor3f (0.f, 0.f, 1.f);
                // glVertex3f (0.f, 0.6f, 0.f);
                // glEnd ();*/

                // glClear (GL_COLOR_BUFFER_BIT);
                // glClearColor (1.f, 0.f, 0.f, 0);
                // glBegin(GL_TRIANGLES);
                // glVertex2d(0.0, 0.0);
                // glVertex2d(0.0, 1.0);
                // glVertex2d(1.0, 0.0);
                // glEnd();


                glfwSwapBuffers (window);
                glfwPollEvents ();
        }

}