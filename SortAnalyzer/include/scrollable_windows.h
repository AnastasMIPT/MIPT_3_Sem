#ifndef SCROLLABLE_WINDOWS_H
#define SCROLLABLE_WINDOWS_H


class IScrollableWindow {
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
};




#endif // SCROLLABLE_WINDOWS_H