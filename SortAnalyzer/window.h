#ifndef WINDOW_H
#define WINDOW_H



#include <list>
#include <GLFW/glfw3.h>
#include <queue>
#include <memory>


class MouseClickEvent {
public:
    double pos_x;
    double pos_y;
    int button;
    int action;
    int mods;

    MouseClickEvent (double _pos_x, double _pos_y, int _button, int _action, int _mods) 
    : pos_x (_pos_x), pos_y (_pos_y), button (_button), action (_action), mods (_mods) {}

    MouseClickEvent () = default;
};



struct Event {
    enum EventTypes {
        MOUSE_CLICK
    } type;
    union {
        MouseClickEvent mouse_click;
    } ev;

    Event (const MouseClickEvent& _mouse_click);
};





class IWindow {
public:
    virtual void draw () const = 0;
    virtual bool onMouseClick (const MouseClickEvent& event) = 0;
    virtual bool CheckCoordinate (double pos_x, double pos_y) const = 0;
    
    
    virtual ~IWindow () = default;
};


class WindowContainer : IWindow {
    using WindowList = std::list<IWindow*>;
    static WindowList subwindows;


    
public:
    typedef WindowList::iterator iterator;
    typedef const    iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;

    iterator begin () {
        return subwindows.begin ();
    }

    iterator end () {
        return subwindows.end ();
    }

    void addWindow (IWindow* window);
    

    bool onMouseClick (const MouseClickEvent& event) override;
    void draw () const override {}
    bool CheckCoordinate (double pos_x, double pos_y) const {return true;}

};



class AbstractApplication {
protected:
    static WindowContainer windows;
    static std::queue <std::unique_ptr<Event>> event_queue;
    
public:
    virtual ~AbstractApplication () = default;
    void addObject (IWindow* window);
    void drawObjects () const;
};



class Application : public AbstractApplication {
    void SetCallbacks ();
public:
    GLFWwindow* app_window;
    Application (int width, int height, const char* name);
    ~Application ();
    static void MouseClickCallback (GLFWwindow* , int, int, int);
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback (int error, const char* description);
    void pollEvent ();
    void run ();
    bool shouldCLose ();
};


#endif //WINDOW_H

