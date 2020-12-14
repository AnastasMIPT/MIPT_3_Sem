#ifndef PAINTER_H
#define PAINTER_H
#include "tools.h"
#include "canvas.h"
#include "window.h"
#include "application.h"
#include "tool_bar.h"

class Painter : public WindowContainer {
    AbstractTool* active_tool;
    Canvas* canvas;
    ToolBar* tools;

    Color active_color;
    bool is_applying = false;

public:
    bool onMouseClick (const MouseClickEvent& event) override;
    void onMouseMove  (const MouseMoveEvent& event)  override;


};



#endif // PAINTER_H