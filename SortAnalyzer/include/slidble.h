#ifndef SLIDBLE_H
#define SLIDBLE_H



class ISlidble {
public:
    virtual void slideByRatio (double ratio) = 0;
    virtual ~ISlidble () = default;
};


template <typename T>
class SlidbleValue : public ISlidble {
    T value;
    T lim_up;
    T lim_down;
public:
    SlidbleValue (const T& value, const T& lim_up, const T& lim_down)
    : value (value), lim_up (lim_up), lim_down (lim_down) {}

    void slideByRatio (double ratio) override;

    T getValue     () const;
    T getLimitUp   () const;
    T getLimitDown () const;

    void setValue (const T& _value);

};


template <typename T>
void SlidbleValue<T>::slideByRatio (double ratio) {
    value = ratio * (lim_up - lim_down);
}

template <typename T>
T SlidbleValue<T>::getValue () const {
    return value;
}

template <typename T>
T SlidbleValue<T>::getLimitUp () const {
    return lim_up;
}


template <typename T>
T SlidbleValue<T>::getLimitDown () const {
    return lim_down;
}

template <typename T>
void SlidbleValue<T>::setValue (const T& _value) {
    value = _value; 
}

#endif // SLIDBLE_H