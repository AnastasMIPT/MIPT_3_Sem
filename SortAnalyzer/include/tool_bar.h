#ifndef TOOL_BAR_H
#define TOOL_BAR_H
#include "tools.h"
#include "window.h"
#include "tool_manager.h"
#include <vector>
#include <memory>


class ToolBar : public WindowContainer {
    static constexpr double top_off  = 0.1;
    static constexpr double left_off = 0.1;

public:
    
    ToolBar (const Rect& _trappings);
    ~ToolBar ();

};


#endif // TOOL_BAR_H