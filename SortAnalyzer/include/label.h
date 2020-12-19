#ifndef LABEL_H
#define LABEL_H

#include "window.h"
#include <string>

class LabelWindow : public AbstractWindow {
    std::string text;
public:
    LabelWindow (const ab::Rect& _trappings);
    LabelWindow (const std::string& _text, const ab::Rect& _trappings);

    void draw () const override;
};


#endif // LABEL_H