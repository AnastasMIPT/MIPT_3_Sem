#ifndef EVENTS_H
#define EVENTS_H

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

class MouseMoveEvent {
public:
    double pos_x;
    double pos_y;


    MouseMoveEvent (double _pos_x, double _pos_y) 
    : pos_x (_pos_x), pos_y (_pos_y) {}

    MouseMoveEvent () = default;
};



struct Event {
    enum EventTypes {
        DEFAULT_EVENT,
        MOUSE_CLICK,
        MOUSE_MOVE
    } type;
    union {
        MouseClickEvent mouse_click;
        MouseMoveEvent mouse_move;
    } ev;

    Event (const MouseClickEvent& _mouse_click);
    Event (const MouseMoveEvent& _mouse_click);
    Event ();
};


#endif // EVENTS_H