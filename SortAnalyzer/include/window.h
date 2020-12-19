#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <queue>
#include <vector>
#include <memory>
#include "events.h"
#include "config.h"

// class IComponent {
// public:
//     virtual void attach () = 0; // ==> subscribe to events
//     virtual void handleEvent () = 0;
//     virtual void disattach () = 0;

//     virtual ~IComponent ();
// };

// class Dragable : IComponent {

// };

// class IsContainer : IComponent {

// };


// class Scrollable : IComponent {

// };


class Object {

};


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
    ab::Rect trappings;
    //unsigned int rect_id;
    /* vector <IComponent*> properties;*/
public:
    AbstractWindow (const ab::Rect& _trappings);
    AbstractWindow () = default;
    bool CheckCoordinate (double pos_x, double pos_y) const override;
    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove (const MouseMoveEvent& event) override {}
    void draw () const override;
    ~AbstractWindow () = default;
};



class WindowContainer : public AbstractWindow {
protected:
    using WindowList = std::vector<IWindow*>;
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

    WindowContainer (const ab::Rect& _trappings);

    void addWindow (IWindow* window);
    

    bool onMouseClick (const MouseClickEvent& event) override;
    //void onMouseMove (const MouseMoveEvent& event) override;
    void draw () const override;
};




class AbstractDragableWindow : public AbstractWindow {
protected:
    bool is_drag = false;
    double off_x = 0;
    double off_y = 0;
public:
    AbstractDragableWindow (const ab::Rect& _trappings)
    : AbstractWindow (_trappings) {}

    AbstractDragableWindow () = default;

    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove  (const MouseMoveEvent& event) override;
    virtual void move (double xpos, double ypos) = 0;
};




#endif //WINDOW_H