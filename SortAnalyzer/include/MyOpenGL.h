#ifndef MYOPENGL_H
#define MYOPENGL_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <queue>
#include <memory>
#include "engine.h"
#include "events.h"
#include <map>

class OpenGL : IEngine {
private:
    GLFWwindow* app_window;
    //std::vector<ab::Rect> rects;
    
    //unsigned int cur_id = 0;
    OpenGL (int width, int height, const char* name);
public:

    static std::queue<std::unique_ptr<Event>> event_que;


    static void MouseClickCallback (GLFWwindow* window, int button, int action, int mods);
    static void MouseMoveCallback (GLFWwindow* window, double xpos, double ypos);
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback (int error, const char* description);

    void drawRect (const Rect& rect) override;
    void drawLine (const Line& line) override;
    void drawTriangle (const Triangle& triangele) override;
    void drawLineStrip (const Vector<Point2d>& points, const Color& color) override;

    static Point2d convertAbstrToRealCoords (const Point2d& abstract_coords);
    static Point2d convertRealToAbstrCoords (const Point2d& real_coords);

    static Rect convertAbstrToRealRect (const Rect& abstract_rect);
    static Rect convertRealToAbstrRect (const Rect& real_rect);


    // unsigned int constructRectForFastDraw (const Rect& rect);
    // void drawRectFast (unsigned int id);

    bool checkCoordsInRect (double pos_x, double pos_y, const Rect& rect);

    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;
    void clear ();



    friend Engine<OpenGL>;
    ~OpenGL ();
};

#endif // MYOPENGL_H