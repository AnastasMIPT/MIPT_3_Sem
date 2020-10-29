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
    void draw () const override;
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
public:
    GLFWwindow* app_window;
    Application () = default;
    ~Application () = default;
    void pollEvent ();
    void run ();
    bool shouldCLose ();
};


#endif //WINDOW_H