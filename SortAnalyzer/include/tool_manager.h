#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.h"
#include "button.h"
#include "plugin.h"

class ToolManager {

    inline static std::vector<AbstractTool*> tools = 
                        {new Pencil (), new Eraser (), new Plugin ("BoxBlur"), new Plugin ("ColorFilter")};

    inline static size_t active_tool;
    //inline static Color active_color = COLORS::GREEN;
    inline static SlidableColor active_color = SlidableColor (COLORS::GREEN);
    inline static SlidableValue<size_t> thickness   = SlidableValue<size_t> (5, 80, 3);
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

    static SlidableValue<size_t>* getSlidableThick ();
    static SlidableColor* getSlidableColor ();

};

#endif // TOOL_MANAGER_H