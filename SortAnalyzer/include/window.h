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
    virtual void onMouseMove (const MouseMoveEvent& event) = 0;
    virtual bool CheckCoordinate (double pos_x, double pos_y) const = 0;
    
    
    virtual ~IWindow () = default;
};



class AbstractWindow : public IWindow {
public:
    Rect trappings;
public:
    AbstractWindow (const Rect& _trappings);
    bool CheckCoordinate (double pos_x, double pos_y) const override;
    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove (const MouseMoveEvent& event) override {}
    void draw () const override;
    ~AbstractWindow () = default;
};



class WindowContainer : public AbstractWindow {
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

    WindowContainer (const Rect& _trappings);

    void addWindow (IWindow* window);
    

    bool onMouseClick (const MouseClickEvent& event) override;
    //void onMouseMove (const MouseMoveEvent& event) override;
    void draw () const override;
};


class IScrollableWindow : IWindow {
public:
    virtual double getRatio () = 0;
    virtual void scrollOnceUp () = 0;
    virtual void scrollOnceDown () = 0;

    virtual ~IScrollableWindow () = default;
};


class AbstractScrollableWindow : public IScrollableWindow {
    int num_of_first_unit = 0;
    int num_of_units;
    int num_of_visable_units;
public:
    AbstractScrollableWindow (int _num_of_units, int _num_of_visable_units);
    double getRatio () override;
    void scrollOnceUp   () override;
    void scrollOnceDown () override;
    void draw () const {}
    bool onMouseClick (const MouseClickEvent& event)   {return false;}
    void onMouseMove  (const MouseMoveEvent&  event)   {}
    bool CheckCoordinate (double pos_x, double pos_y) const override {return false;}

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



class AbstractDragableWindow : public AbstractWindow {
protected:
    bool is_drag = false;
    double off_x = 0;
    double off_y = 0;
public:
    AbstractDragableWindow (const Rect& _trappings)
    : AbstractWindow (_trappings) {}
    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove (const MouseMoveEvent& event) override;
    virtual void move (double xpos, double ypos) = 0;
};




#endif //WINDOW_H