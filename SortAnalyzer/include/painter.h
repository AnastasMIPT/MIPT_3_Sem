#ifndef PAINTER_H
#define PAINTER_H
#include "tools.h"
#include "canvas.h"
#include "window.h"
#include "application.h"
#include "tool_manager.h"

class Painter : WindowContainer {
    AbstractTool* active_tool;
    Canvas* canvas;
    ToolManager* tools;

    Color active_color;
    bool is_applying = false;

public:
    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove  (const MouseMoveEvent& event)  override;


};



#endif // PAINTER_H