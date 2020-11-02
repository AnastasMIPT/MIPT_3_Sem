#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <queue>
#include <memory>
#include "events.h"
#include "config.h"

class IWindow {
public:
    virtual void draw () const = 0;
    virtual bool onMouseClick (const MouseClickEvent& event) = 0;
    //virtual void onMouseMove (const MouseMoveEvent& event) = 0;
    virtual bool CheckCoordinate (double pos_x, double pos_y) const = 0;
    
    
    virtual ~IWindow () = default;
};

class QuadWindow : public IWindow {
public:
    double x;
    double y;
    double size_x;
    double size_y;
    Color color;
public:
    QuadWindow (double _x, double _y, double _size_x, double _size_y, const Color& _color = Color ());
    bool CheckCoordinate (double pos_x, double pos_y) const override;
    bool onMouseClick (const MouseClickEvent& event) override;
    //void onMouseMove (const MouseMoveEvent& event) override {}
    void draw () const override;
    ~QuadWindow () = default;
};



class WindowContainer : public QuadWindow {
protected:
    using WindowList = std::list<IWindow*>;
    WindowList subwindows;

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

    WindowContainer (double _x, double _y, double _size_x, double _size_y, const Color& _color = Color ());

    void addWindow (IWindow* window);
    

    bool onMouseClick (const MouseClickEvent& event) override;
    //void onMouseMove (const MouseMoveEvent& event) override;
    void draw () const override;
};


class IScrollableWindow {
public:
    virtual void scrollOnceUp () = 0;
    virtual void scrollOnceDown () = 0;

    virtual ~IScrollableWindow () = default;
};

class IDragableWindow {
    
public:
    virtual void drag () = 0;
    virtual bool isDraging () const = 0;
    virtual ~IDragableWindow () = default;
};



class AbstractApplication {
protected:
    static WindowContainer windows;
    static std::queue <std::unique_ptr<Event>> event_queue;
    static IWindow* active_window;
public:
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
};



class AbstractDragableWindow : QuadWindow, IDragableWindow {
    bool is_drag = false;
public:
    bool isDraging () const override {return is_drag;}
    bool onMouseClick (const MouseClickEvent& event) override {

        if (event.button == GLFW_MOUSE_BUTTON_LEFT) {
            if(GLFW_PRESS == event.action && CheckCoordinate (event.pos_x, event.pos_y)) {
                is_drag = true;
                Application::setActiveWindow (this); 
            }
            else if (GLFW_RELEASE == event.action) {
                is_drag = false;
                Application::setActiveWindow (NULL);
            }
        }
    }


    void drag ();
};


#endif //WINDOW_H