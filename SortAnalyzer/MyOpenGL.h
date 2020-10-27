#ifndef MYOPENGL_H
#define MYOPENGL_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "engine.h"


class OpenGL : IEngine {
private:
    GLFWwindow* main_window;
    OpenGL ();
public:
    void drawRect () {printf ("OpenGl rect\n");}
    
    friend Engine<OpenGL>;
    ~OpenGL ();
};

#endif // MYOPENGL_H