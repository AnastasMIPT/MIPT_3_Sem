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
    //static void MouseMoveCallback (GLFWwindow* window, double xpos, double ypos);
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback (int error, const char* description);

    void drawRect (const Rect& rect) override;
    void drawTriangle (const Triangle& triangele) override;
    void drawLine (const Line& line) override;
    void drawLineStrip (const Vector<Point2d>& points, const Color& color) override;

    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;

    friend Engine<OpenGL>;
    ~OpenGL ();
};

#endif // MYOPENGL_H