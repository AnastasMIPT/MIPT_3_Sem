#include "MyOpenGL.h"

OpenGL::OpenGL () {
    if  (!glfwInit ()) exit (EXIT_FAILURE);
}

OpenGL::~OpenGL () {
    glfwTerminate ();
    exit (EXIT_SUCCESS);
}

