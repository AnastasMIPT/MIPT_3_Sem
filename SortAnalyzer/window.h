#ifndef WINDOW_H
#define WINDOW_H



#include <list>
#include <GLFW/glfw3.h>
#include <queue>
#include <memory>

enum EventTypes {
    MOUSE_CLICK
};


class AbstractEvent {
public:
    unsigned int type;
    bool is_coordinatble;
    
    AbstractEvent (unsigned int _type, bool _is_coordinatable)
    : type (_type), is_coordinatble (_is_coordinatable) {}
    
    virtual ~AbstractEvent () = default;
};


class CoordinatbleEvent : public AbstractEvent{
public:
    double pos_x;
    double pos_y;
    
    CoordinatbleEvent (double _pos_x, double _pos_y, unsigned int _type)
    : AbstractEvent (_type, true), pos_x (_pos_x), pos_y (_pos_y) {}
};

class MouseClickEvent : public CoordinatbleEvent {
public:
    int button;
    int action;
    int mods;

    MouseClickEvent (double _pos_x, double _pos_y, int _button, int _action, int _mods) 
    : CoordinatbleEvent (_pos_x, _pos_y, MOUSE_CLICK), button (_button), action (_action), mods (_mods) {}
};





class AbstractWindow {
public:
    virtual void draw () const = 0;
    virtual void onMouseClick (MouseClickEvent* event) = 0;
    virtual bool CheckCoordinate (double pos_x, double pos_y) const = 0;
    virtual bool HandleEvent (AbstractEvent* event);
    
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
    void onMouseClick (MouseClickEvent* event) {}
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
    

    bool HandleEvent (AbstractEvent* event) override;
    void onMouseClick (MouseClickEvent* event) override {}
    void draw () const override {}
    bool CheckCoordinate (double pos_x, double pos_y) const {return true;}

};



class AbstractApplication {
protected:
    static AbstractWindowContainer windows;
    static std::queue <std::unique_ptr<AbstractEvent>> event_queue;
    
public:
    virtual ~AbstractApplication () = default;
    void addObject (AbstractWindow* window);
    void drawObjects () const;
};



class SortAnalyzer : public AbstractApplication {
public:
    static void MouseClickCallback (GLFWwindow* , int, int, int);
    void run ();
    
};


#endif //WINDOW_H

