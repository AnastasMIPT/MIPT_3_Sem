#include "scroll_bar.h"
#include "button.h"
#include <iostream>

ScrollBar::ScrollBar (IScrollableWindow* _scroll_window, const Rect& _trappings)
: WindowContainer (_trappings),
  scroll_window (_scroll_window) {

    is_vertical = trappings.height > trappings.width;
    
    double s_bar_x = trappings.coords.x;
    double s_bar_y = trappings.coords.y;
    double s_bar_w = trappings.width;
    double s_bar_h = trappings.height;



    if (is_vertical) {
        arrow_up = new ::Button<ScrollFunctor> ({{s_bar_x, s_bar_y + s_bar_h - but_size}, 
                                       s_bar_w, but_size, but_color}, 
                                       scroll_window, but_color, true, is_vertical);

        double slider_size = (s_bar_h - 2 * but_size) * scroll_window->getRatio (is_vertical);
        slider = Slider ({{s_bar_x, s_bar_y + s_bar_h - slider_size - but_size}, 
                 s_bar_w, slider_size, 
                 slider_color}, s_bar_y + s_bar_h - but_size, s_bar_y + but_size,
                 scroll_window, is_vertical);



        arrow_down = new ::Button<ScrollFunctor>  ({{s_bar_x, s_bar_y}, 
                                                 s_bar_w, but_size, but_color},
                                                 scroll_window, but_color, false, is_vertical);
    } else {
        // HORIZONTAL
        printf ("horizontal\n");
        arrow_down = new ::Button<ScrollFunctor>  ({{s_bar_x, s_bar_y}, 
                                                 but_size, s_bar_h, but_color},
                                                 scroll_window, but_color, true, is_vertical);
        double slider_size = (s_bar_w - 2 * but_size) * scroll_window->getRatio (is_vertical);
        slider = Slider ({{s_bar_x + but_size, s_bar_y}, 
                 slider_size, s_bar_h, 
                 slider_color}, s_bar_x + s_bar_w - but_size, s_bar_x + but_size,
                 scroll_window, is_vertical);

        arrow_up = new ::Button<ScrollFunctor> ({{s_bar_x + s_bar_w - but_size, s_bar_y}, 
                                       but_size, s_bar_h, but_color}, 
                                       scroll_window, but_color, false, is_vertical);
    }
    

    subwindows.push_back (arrow_up);
    subwindows.push_back (&slider); 
    subwindows.push_back (arrow_down);
}


bool ScrollBar::onMouseClick (const MouseClickEvent& event) {
    for (auto window : subwindows) {
        window->onMouseClick (event);
    }
    
    if (event.button == MouseButtonTypes::LEFT &&
        event.action == MouseButtonActions::PRESS &&
        CheckCoordinate (event.pos_x, event.pos_y)) {

        slider.jumpToCoord (event.pos_x, event.pos_y);
        scroll_window->slideByRatio (slider.getRatio (), is_vertical);
    }
}



Slider::Slider (const Rect& _trappings, double _limit_up, 
                double _limit_down, ISlidable* _slidable_wind, bool _is_vertical)
    : AbstractDragableWindow (_trappings),
      limit_up (_limit_up), limit_down (_limit_down), slidable_wind (_slidable_wind),
      is_vertical (_is_vertical) {}


bool Slider::jumpIsPossible (double x, double y) {
    if (is_vertical) {
        return  y >= limit_down &&
                y <= limit_up &&
                x >= trappings.coords.x &&
                x <= trappings.coords.x + trappings.width;
    } else {
        return  x >= limit_down &&
                x <= limit_up &&
                y >= trappings.coords.y &&
                y <= trappings.coords.y + trappings.height;
    }
}

void Slider::jumpToCoord (double x, double y) {
    if (jumpIsPossible (x, y)) {
        if (is_vertical) {
            double coord_new = y - trappings.height / 2;
            if (coord_new + trappings.height > limit_up) {
                trappings.coords.y = limit_up - trappings.height;
            } else if (coord_new < limit_down) {
                trappings.coords.y = limit_down;
            } else {
                trappings.coords.y = coord_new;    
            }
        } else {
            double coord_new = x - trappings.width / 2;
            if (coord_new + trappings.width > limit_up) {
                trappings.coords.x = limit_up - trappings.width;
            } else if (coord_new < limit_down) {
                trappings.coords.x = limit_down;
            } else {
                trappings.coords.x = coord_new;    
            }
        }
    }
}

double Slider::getRatio () {
    if (is_vertical) {
        double numerator   = limit_up - trappings.height - trappings.coords.y;
        double denominator = limit_up - trappings.height - limit_down;
        return numerator / denominator;
    } else {
        double numerator   = trappings.coords.x - limit_down;
        double denominator = limit_up - (limit_down + trappings.width);
        return numerator / denominator;
    }
    
}

void Slider::move (double posx, double posy) {
    if (is_vertical) {
        double new_y = posy - off_y;
        printf ("move: pos_x = %lf, pos_y = %lf, new_y = %lf\n", posx, posy, new_y);
        if (limit_down < new_y && new_y + trappings.height < limit_up) {
            printf ("yes\n");
            trappings.coords.y = new_y;
            slidable_wind->slideByRatio (getRatio (), is_vertical);
        }
    } else {
        double new_x = posx - off_x;
        printf ("move: pos_x = %lf, pos_y = %lf, new_x = %lf\n", posx, posy, new_x);
        if (limit_down < new_x && new_x + trappings.width < limit_up) {
            printf ("yes\n");
            trappings.coords.x = new_x;
            slidable_wind->slideByRatio (getRatio (), is_vertical);
        }
    }
    
}
