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
    bool CheckCoordinate (double pos_x, double pos_y) const override {return true;}

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

