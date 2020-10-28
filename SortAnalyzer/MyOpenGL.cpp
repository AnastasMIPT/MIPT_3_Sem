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

}

OpenGL::~OpenGL () {
    glfwDestroyWindow (app_window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
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

    std::unique_ptr<Event> event (new Event (MouseClickEvent (x_pos, y_pos, button, action, mods)));
    event_que.push (std::move (event));
    printf ("Пойман щелчок мыши\n");
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

void OpenGL::drawRect (double x, double y, double width, double height, const Color& color) {
    glBegin (GL_QUADS);
        glColor3f (color.red, color.green, color.blue);
        glVertex2d (x, y);
        glVertex2d (x, y + height);
        glVertex2d (x + width, y + height);
        glVertex2d (x + width, y);
    glEnd ();
}