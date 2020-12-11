#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"



class AbstractApplication {
protected:
    inline static WindowContainer windows = 
        WindowContainer ({0.0, 0.0, 1.0, 1.0, COLORS::DEFAULT_BACKGROUND});

    inline static std::queue <std::unique_ptr<Event>> event_queue;
    inline static IWindow* active_window = NULL;
public:

    AbstractApplication ();
    virtual ~AbstractApplication () = default;
    static void addObject (IWindow* window);
    static void drawObjects ();
    static void setActiveWindow (IWindow* window);
};



class Application : public AbstractApplication {
public:
    Application () = delete;
    static void pollEvent ();
    static void run ();
    static bool shouldCLose ();
    static void loadImages ();
};



#endif // APPLICATION_H