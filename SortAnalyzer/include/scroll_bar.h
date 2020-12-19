#ifndef SCROLL_BAR_H
#define SCROLL_BAR_H

#include "color.h"
#include "window.h"
#include "scrollable_windows.h"



class Slider : public AbstractDragableWindow {
    double limit_up;
    double limit_down;
    bool is_vertical;
    ISlidable* slidable_wind;

    
public:
    Slider (const Rect& _trappings, double _limit_up, double _limit_down,
            ISlidable* _slidable_wind, bool _is_vertical = true);

    Slider () = default;

    double getRatio ();
    bool jumpIsPossible (double x, double y);
    void jumpToCoord (double x, double y);
    void move (double xpos, double ypos);
};

class ScrollBar : public WindowContainer {
    IScrollableWindow* scroll_window;
    ::AbstractWindow* arrow_up;
    Slider slider;
    ::AbstractWindow* arrow_down;
    bool is_vertical;

    static constexpr Color but_color = COLORS::DEFAULT_BUTTON;
    static constexpr Color slider_color = COLORS::DEFAULT_SLIDER;
    static constexpr double but_size = 0.1;

public:
    ScrollBar (IScrollableWindow* _scroll_window, const Rect& _trappings);

    bool onMouseClick (const MouseClickEvent& event) override;
};




#endif // SCROLL_BAR_H