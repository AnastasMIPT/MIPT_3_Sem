#include "painter.h"


bool Painter::onMouseClick (const MouseClickEvent& event) {
    printf ("Painter: onClick\n");
    if (event.button == MouseButtonTypes::LEFT) {
        printf ("Left buton\n");
        auto* active_tool = ToolManager::getActiveTool ();
        Point2d canvas_coords = canvas->convertToCanvasCoords ({event.pos_x, event.pos_y});
    
        if(MouseButtonActions::PRESS == event.action
           && canvas->CheckCoordinate (event.pos_x, event.pos_y)) {
            
            is_applying = true;
            Application::setActiveWindow (this);
            active_tool->startApplying (canvas, canvas_coords.x, canvas_coords.y);
            return true;
        }
        else if (MouseButtonActions::RELEASE == event.action && is_applying) {
            
            is_applying = false;
            Application::setActiveWindow (NULL);
            active_tool->finishApplying (canvas, canvas_coords.x, canvas_coords.y);
        }
        tools->onMouseClick (event);
    }
}

void Painter::onMouseMove (const MouseMoveEvent& event) {
    Point2d canvas_coords = canvas->convertToCanvasCoords ({event.pos_x, event.pos_y});
    auto* active_tool = ToolManager::getActiveTool ();
    printf ("cc anc = %lf, %lf\n", canvas_coords.x, canvas_coords.y);
    active_tool->apply (canvas, canvas_coords.x, canvas_coords.y);
}

Painter::Painter (Canvas* _canvas, ToolBar* _tools)
: WindowContainer ({}), canvas (_canvas), tools (_tools) {
    WindowContainer::addWindow (_canvas);
    WindowContainer::addWindow (_tools);
}