#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.h"
#include "button.h"

class ToolManager {

    inline static std::vector<AbstractTool*> tools = 
                        {new Pencil (), new Eraser ()};

    inline static size_t active_tool;
    inline static Color active_color = COLORS::GREEN;
    inline static size_t thickness   = 5;
    inline static Button<ToolFunctor>* active_tool_but;

public:
    ToolManager () = delete;

    static void setActiveToolBut  (Button<ToolFunctor>* but);
    static void setActiveTool     (size_t tool_id);
    static void setThickness      (size_t _thickness);
    static void setAcitveColor    (Color _color);
    
    static Button<ToolFunctor>* getAcitveToolBut ();
    static AbstractTool* getActiveTool    ();
    static size_t        getThickness     ();
    static Color         getAcitveColor   ();
    static size_t        getActiveToolId  ();
    

};

#endif // TOOL_MANAGER_H