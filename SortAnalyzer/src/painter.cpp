#include "painter.h"


bool Painter::onMouseClick (const MouseClickEvent& event) {

    if (event.button == MouseButtonTypes::LEFT) {
        
        if(MouseButtonActions::PRESS == event.action
           && canvas->CheckCoordinate (event.pos_x, event.pos_y)) {
            
            is_applying = true;
            Application::setActiveWindow (this);
            active_tool->startApplying ();
            return true;
        }
        else if (MouseButtonActions::RELEASE == event.action && is_applying) {
            
            is_applying = false;
            Application::setActiveWindow (NULL);
            active_tool->finishApplying ();
        }

        tools->onMouseClick (event);
    }
}

void Painter::onMouseMove (const MouseMoveEvent& event) {
    Point2d canvas_coords = canvas->convertToCanvasCoords ({event.pos_x, event.pos_y});
    active_tool->apply (canvas, canvas_coords.x, canvas_coords.y);
}