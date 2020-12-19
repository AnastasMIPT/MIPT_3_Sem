#ifndef SCROLLABLE_WINDOWS_H
#define SCROLLABLE_WINDOWS_H
#include "slidable.h"



class IScrollableWindow : public ISlidable {
public:
    virtual double getRatio (bool is_vertical) = 0;
    virtual void scrollOnceUp (bool is_vertical) = 0;
    virtual void scrollOnceDown (bool is_vertical) = 0;
    //virtual void slideByRatio (double ratio) = 0;
};


class AbstractScrollableWindow : public IScrollableWindow {
    int num_of_first_unit = 0;
    int num_of_units;
    int num_of_visable_units;
public:
    AbstractScrollableWindow (int _num_of_units, int _num_of_visable_units);
    double getRatio (bool is_vertical) override;
    void scrollOnceUp    (bool is_vertical) override;
    void scrollOnceDown  (bool is_vertical) override;
    void slideByRatio   (double retio, bool is_vertical) override;
};




#endif // SCROLLABLE_WINDOWS_H