#include "label.h"

void LabelWindow::draw () const {
    AbstractWindow::draw ();
    GEngine::system.drawText (text, trappings.coords);
}


LabelWindow::LabelWindow (const ab::Rect& _trappings)
: AbstractWindow (_trappings) {}

LabelWindow::LabelWindow (const std::string& _text, const ab::Rect& _trappings) 
: AbstractWindow (_trappings), text (_text) {}