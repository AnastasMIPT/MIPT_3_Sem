
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode);
const GLuint WIDTH = 800, HEIGHT = 600;


// https://habr.com/ru/post/311808/


// g++ -c  Graphics.cpp -o Graphics.o
// g++ Graphics.o -o Graphics -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi
//  ./Graphics

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2i(250, 450);
            glColor3f(0.0, 0.0, 1.0);
            glVertex2i(250, 150);
            glColor3f(0.0, 1.0, 0.0);
            glVertex2i(550, 150);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2i(550, 450);
        glEnd();
        
    
}



int main ()
{
    printf ("Starting GLFW context, OpenGL 3.3\n");
    // Init GLFW
    glfwInit ();
    // Set all the required options for GLFW
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow (WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);    
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate ();
        return -1;
    }

    glfwMakeContextCurrent (window);
    // Set the required callback functions
    glfwSetKeyCallback (window, key_callback);



    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize (window, &width, &height);  
    glViewport (0, 0, width, height);

    GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  



    // Game loop
    while (!glfwWindowShouldClose (window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents ();

        // Render
        // Clear the colorbuffer
        glClearColor (0.2f, 0.3f, 0.6f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);
       
        // Swap the screen buffers
        glfwSwapBuffers (window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate ();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode)
{
    printf ("%d\n", key);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);

}