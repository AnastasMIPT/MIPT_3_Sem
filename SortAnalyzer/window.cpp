#include "window.h"

Application::Application (int width, int height, const char* name) {
    if  (!glfwInit ()) exit (EXIT_FAILURE);

    app_window = glfwCreateWindow (width, height, name, NULL, NULL);
    if (!app_window) {
        glfwTerminate ();
        exit (EXIT_FAILURE);
    }


    glfwMakeContextCurrent (app_window);
    SetCallbacks ();

}

void Application::SetCallbacks () {
    glfwSetErrorCallback (Application::ErrorCallback);
    glfwSetKeyCallback (app_window, Application::KeyCallback);
    glfwSetMouseButtonCallback (app_window, Application::MouseClickCallback);
}

void Application::pollEvent () {
    if (!event_queue.empty ()) {
        Event* event = event_queue.front ().get ();
        bool is_consumed = false;
        switch (event->type)
        {
        case Event::EventTypes::MOUSE_CLICK:
            is_consumed = windows.onMouseClick (event->ev.mouse_click);
            break;
        default:
            printf ("неизвестный тип события\n");
        }
        if (is_consumed) printf ("Событие обработано\n");
        event_queue.pop ();
    }
}

Application::~Application () {
    glfwDestroyWindow (app_window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
}

void Application::run () {
    drawObjects ();
    glfwSwapBuffers (app_window);
    glfwPollEvents ();
    pollEvent ();
}

bool Application::shouldCLose () {
    return glfwWindowShouldClose (app_window);
}

void Application::MouseClickCallback (GLFWwindow* window, int button, int action, int mods) {
    double x_pos (0), y_pos (0);
    glfwGetCursorPos (window, &x_pos, &y_pos);
    int width, height;
    glfwGetWindowSize (window, &width, &height);

    x_pos = x_pos * 2 / width  - 1;
    y_pos = -(y_pos * 2 / height - 1);

    std::unique_ptr<Event> event (new Event (MouseClickEvent (x_pos, y_pos, button, action, mods)));
    event_queue.push (std::move (event));
    printf ("Пойман щелчок мыши\n");
}

void Application::KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if  (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);
}

void Application::ErrorCallback (int error, const char* description) {
    fputs (description, stderr);
}




Event::Event (const MouseClickEvent& _mouse_click) : type (MOUSE_CLICK) {
    ev.mouse_click = _mouse_click;
}


void AbstractApplication::addObject (IWindow* window) {
    windows.addWindow (window);
}

void AbstractApplication::drawObjects () const {
    for (auto window : windows) {
        window->draw ();
    }
}

void WindowContainer::addWindow (IWindow* window) {
    subwindows.push_back (window);
}


bool WindowContainer::onMouseClick (const MouseClickEvent& event) {
    printf ("Принял событие\n");

    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false;
  
    printf ("у события нужные координаты\n");
    for (auto window : subwindows) {
        is_consumed = window->onMouseClick (event);
        if (is_consumed) return true;
    }
    printf ("событие не поглащено\n");


}
