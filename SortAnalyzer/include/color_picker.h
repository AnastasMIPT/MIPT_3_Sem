#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "color.h"
#include "label.h"
#include "fader.h"


class ColorPicker  : public WindowContainer{
    SlidableColor* color;
    ::AbstractWindow color_disp;
    Fader<double> red;
    Fader<double> green;
    Fader<double> blue;
//    Fader<double> alpha;

    static constexpr double off = 0.02;
    static constexpr double disp_col_rat = 0.25;


public:
    ColorPicker (const Rect& _trap, SlidableColor* _color);

    bool onMouseClick (const MouseClickEvent& event) override;
};


#endif // COLOR_PICKER