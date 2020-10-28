#ifndef MYOPENGL_H
#define MYOPENGL_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <queue>
#include <memory>
#include "engine.h"
#include "events.h"

class OpenGL : IEngine {
private:
    GLFWwindow* app_window;
    OpenGL (int width, int height, const char* name);
public:

    static std::queue<std::unique_ptr<Event>> event_que;

    static void MouseClickCallback (GLFWwindow* window, int button, int action, int mods);
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback (int error, const char* description);

    void drawRect () override {printf ("OpenGl rect\n");}
    void createAppWindow (int width, int height, const char* name);
    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;

    friend Engine<OpenGL>;
    ~OpenGL ();
};

#endif // MYOPENGL_H