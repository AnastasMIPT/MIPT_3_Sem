#ifndef SETTING_WINDOW
#define SETTING_WINDOW
#include "fader.h"
#include "label.h"

template <typename T>
class SettingWindow : public WindowContainer{
    SlidableValue<T>* value;
    LabelWindow label;
    Fader<T> fader;
    
    static constexpr double label_h = 0.01;
    static constexpr double fader_h = 0.02;
    static constexpr double off_top = 0.002;
    static constexpr double off     = 0.001;
public:
    
    SettingWindow (const Rect& _trappings, SlidableValue<T>* _value, 
                                            const std::string& _label);

    

};



template <typename T>
SettingWindow<T>::SettingWindow (const Rect& _trappings, SlidableValue<T>* _value, 
                                            const std::string& _label) 
: WindowContainer (_trappings), value (_value), 

  label (_label, {trappings.coords.x + off,
        trappings.coords.y + trappings.height - off_top - label_h,
        trappings.width - 2 * off, label_h, _trappings.color}),

  fader (Rect {label.trappings.coords.x, 
        trappings.coords.y + trappings.height - label_h - 2 * off_top - fader_h - 0.1,
                       label.trappings.width, fader_h, _trappings.color},
                       _value)
{
    subwindows.push_back (&label);
    subwindows.push_back (&fader);
}




#endif // SETTING_WINDOW