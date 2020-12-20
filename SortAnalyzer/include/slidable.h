#ifndef SLIDABLE_H
#define SLIDABLE_H



class ISlidable {
public:
    virtual void slideByRatio (double ratio, bool is_vertical) = 0;
    virtual ~ISlidable () = default;
};


template <typename T>
class SlidableValue : public ISlidable {
    T value;
    T lim_up;
    T lim_down;
public:
    SlidableValue (const T& value, const T& lim_up, const T& lim_down)
    : value (value), lim_up (lim_up), lim_down (lim_down) {}

    SlidableValue () = default;

    void slideByRatio (double ratio, bool is_vertical = true) override;

    T getValue     () const;
    T getLimitUp   () const;
    T getLimitDown () const;

    void setValue (const T& _value);

};


template <typename T>
void SlidableValue<T>::slideByRatio (double ratio, bool is_vertical) {
    value = ratio * (lim_up - lim_down);
}

template <typename T>
T SlidableValue<T>::getValue () const {
    return value;
}

template <typename T>
T SlidableValue<T>::getLimitUp () const {
    return lim_up;
}


template <typename T>
T SlidableValue<T>::getLimitDown () const {
    return lim_down;
}

template <typename T>
void SlidableValue<T>::setValue (const T& _value) {
    value = _value; 
}

#endif // SLIDABLE_H