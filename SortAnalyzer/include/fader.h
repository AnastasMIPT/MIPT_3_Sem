#ifndef FADER_H
#define FADER_H


#include "scroll_bar.h"
#include "label.h"
#include "color.h"

template <typename T>
class Fader : public WindowContainer {
    SlidableValue<T>* val;
    Slider slider;
    ::AbstractWindow pin;

    static constexpr double slider_size = 0.01;
    static constexpr double pin_rat = 0.2;
    static constexpr Color slider_color = COLORS::DEFAULT_SLIDER;

public:
    Fader (const Rect& _trappings, SlidableValue<T>* _val, const Color& _pin_color);

    bool onMouseClick (const MouseClickEvent& event) override;
};




template <typename T>
bool Fader<T>::onMouseClick (const MouseClickEvent& event) {
    WindowContainer::onMouseClick (event);

    if (event.button == MouseButtonTypes::LEFT &&
        event.action == MouseButtonActions::PRESS &&
        CheckCoordinate (event.pos_x, event.pos_y)) {

        slider.jumpToCoord (event.pos_x, event.pos_y);
        val->slideByRatio (slider.getRatio (), false);
    }
}



template <typename T>
Fader<T>::Fader (const Rect& _trappings, SlidableValue<T>* _val, const Color& _pin_color)
: WindowContainer (_trappings), val (_val) {

    slider = Slider ({trappings.coords, slider_size, trappings.height, slider_color}, 
                     trappings.coords.x + trappings.width, trappings.coords.x,
                     _val, false);

    double pin_h = trappings.height * pin_rat;
    double pin_y = trappings.coords.y + trappings.height / 2 - pin_h / 2;
    pin = ::AbstractWindow ({trappings.coords.x, pin_y, trappings.width, pin_h, _pin_color});

    subwindows.push_back (&pin);
    subwindows.push_back (&slider);
}



#endif // FADER_H
