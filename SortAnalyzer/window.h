#ifndef WINDOW_H
#define WINDOW_H



#include <list>
#include <GLFW/glfw3.h>
#include <queue>
#include <memory>

enum EventTypes {
    MOUSE_CLICK
};

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
    unsigned int type;
    union {
        MouseClickEvent mouse_click;
    } ev;

    Event (const MouseClickEvent& _mouse_click);
};





class AbstractWindow {
public:
    virtual void draw () const = 0;
    virtual bool onMouseClick (const MouseClickEvent& event) = 0;
    virtual bool CheckCoordinate (double pos_x, double pos_y) const = 0;
    
    
    virtual ~AbstractWindow () = default;
};



class QuadWindow : public AbstractWindow {
public:
    double x;
    double y;
    double size_x;
    double size_y;
public:
    QuadWindow (double _x, double _y, double _size_x, double _size_y);
    bool CheckCoordinate (double pos_x, double pos_y) const;
    bool onMouseClick (const MouseClickEvent& event) {}
    void draw () const {}

    ~QuadWindow () = default;
};






class AbstractWindowContainer : AbstractWindow {
    using WindowList = std::list<AbstractWindow*>;
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

    void addWindow (AbstractWindow* window);
    

    bool onMouseClick (const MouseClickEvent& event) override;
    void draw () const override {}
    bool CheckCoordinate (double pos_x, double pos_y) const {return true;}

};



class AbstractApplication {
protected:
    static AbstractWindowContainer windows;
    static std::queue <std::unique_ptr<Event>> event_queue;
    
public:
    virtual ~AbstractApplication () = default;
    void addObject (AbstractWindow* window);
    void drawObjects () const;
};



class SortAnalyzer : public AbstractApplication {
    void SetCallbacks ();
public:
    GLFWwindow* app_window;
    SortAnalyzer (int width, int height, const char* name);
    ~SortAnalyzer ();
    static void MouseClickCallback (GLFWwindow* , int, int, int);
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback (int error, const char* description);
    void pollEvent ();
    void run ();
    bool shouldCLose ();
};


#endif //WINDOW_H

