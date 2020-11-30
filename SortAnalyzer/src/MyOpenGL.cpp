#include "MyOpenGL.h"

std::queue <std::unique_ptr<Event>> OpenGL::event_que;

OpenGL::OpenGL (int width, int height, const char* name) {
    if  (!glfwInit ()) exit (EXIT_FAILURE);
    app_window = glfwCreateWindow (width, height, name, NULL, NULL);
    if (!app_window) {
        glfwTerminate ();
        exit (EXIT_FAILURE);
    }


    glfwMakeContextCurrent (app_window);
   
    glfwSetMouseButtonCallback (app_window, MouseClickCallback);
    glfwSetKeyCallback (app_window, KeyCallback);
    glfwSetErrorCallback (ErrorCallback);
    glfwSetCursorPosCallback (app_window, MouseMoveCallback);

}

OpenGL::~OpenGL () {
    glfwDestroyWindow (app_window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
}

void OpenGL::clear () {
    glClear (GL_COLOR_BUFFER_BIT);
}

std::unique_ptr<Event> OpenGL::pollEvent () {

    glfwSwapBuffers (app_window);
    glfwPollEvents ();
    std::unique_ptr<Event> res = std::make_unique<Event>();
    if (!event_que.empty ()) {
        res = std::move (event_que.front ());
        event_que.pop ();
    }
    return res;
}

void OpenGL::MouseClickCallback (GLFWwindow* window, int button, int action, int mods) {
    double x_pos (0), y_pos (0);
    glfwGetCursorPos (window, &x_pos, &y_pos);
    int width, height;
    glfwGetWindowSize (window, &width, &height);

    x_pos = x_pos * 2 / width  - 1;
    y_pos = -(y_pos * 2 / height - 1);

    Point2d abstr_coords = convertRealToAbstrCoords ({x_pos, y_pos});
    std::unique_ptr<Event> event (new Event (MouseClickEvent (abstr_coords.x, abstr_coords.y, button, action, mods)));
    event_que.push (std::move (event));
    printf ("Пойман щелчок мыши\n");
}

void OpenGL::MouseMoveCallback (GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize (window, &width, &height);
    xpos = xpos * 2 / width  - 1;
    ypos = -(ypos * 2 / height - 1);
    Point2d abstr_coords = convertRealToAbstrCoords ({xpos, ypos});
    std::unique_ptr<Event> event (new Event (MouseMoveEvent (abstr_coords.x, abstr_coords.y)));
    event_que.push (std::move (event));
}

bool OpenGL::shouldClose () {
    return glfwWindowShouldClose (app_window);
}

void OpenGL::KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if  (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);
}

void OpenGL::ErrorCallback (int error, const char* description) {
    fputs (description, stderr);
}

void OpenGL::drawRect (const Rect& _rect) {
    Rect rect = convertAbstrToRealRect (_rect);
    glBegin (GL_QUADS);
        glColor3f (rect.color.red, rect.color.green, rect.color.blue);
        glVertex2d (rect.coords.x, rect.coords.y);
        glVertex2d (rect.coords.x, rect.coords.y + rect.height);
        glVertex2d (rect.coords.x + rect.width, rect.coords.y + rect.height);
        glVertex2d (rect.coords.x + rect.width, rect.coords.y);
    glEnd ();
}

void OpenGL::drawTriangle (const Triangle& triangele) {
    glBegin (GL_TRIANGLES);
        glColor3f (triangele.color.red, triangele.color.green, triangele.color.blue);
        glVertex2d (triangele.first_p.x, triangele.first_p.y);
        glVertex2d (triangele.second_p.x, triangele.second_p.y);
        glVertex2d (triangele.third_p.x, triangele.third_p.y);
    glEnd ();
}

void OpenGL::drawLine (const Line& line) {
    glBegin (GL_LINE_STRIP);
            glColor3f (line.color.red, line.color.green, line.color.blue);
            glVertex2d (line.first_p.x, line.first_p.y);
            glVertex2d (line.second_p.x, line.second_p.y);
    glEnd ();
}

void OpenGL::drawLineStrip (const Vector<Point2d>& points, const Color& color) {
    glBegin (GL_LINE_STRIP);
        glColor3f (color.red, color.green, color.blue);
        for (size_t i = 0; i < points.size (); ++i) {
            glVertex2d (points[i].x, points[i].y);
        }
    glEnd ();
}


Point2d OpenGL::convertAbstrToRealCoords (const Point2d& abstract_coords) {
    return Point2d {abstract_coords.x * 2 - 1.0, abstract_coords.y * 2 - 1.0};
}

Point2d OpenGL::convertRealToAbstrCoords (const Point2d& real_coords) {
    return Point2d {real_coords.x * 0.5 + 0.5, real_coords.y * 0.5 + 0.5};
}

Rect OpenGL::convertAbstrToRealRect (const Rect& abstract_rect) {
    return {abstract_rect.coords.x * 2 - 1.0, abstract_rect.coords.y * 2 - 1.0,
            abstract_rect.width * 2, abstract_rect.height * 2, abstract_rect.color};
}
    
Rect OpenGL::convertRealToAbstrRect (const Rect& real_rect) {
    return {};
}


bool OpenGL::checkCoordsInRect (double pos_x, double pos_y, const Rect& rect) {
    double rec_x = rect.coords.x;
    double rec_y = rect.coords.y;
    return pos_x > rec_x && 
           pos_y > rec_y && 
           pos_x < rec_x + rect.width && 
           pos_y < rec_y + rect.height?  true : false;
}