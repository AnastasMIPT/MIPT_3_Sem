#include "tools.h"


class ToolManager {

    inline static AbstractTool* active_tool;
    inline static Color active_color = COLORS::GREEN;
    inline static size_t thickness   = 5;

public:
    ToolManager () = delete;

    static void setActiveTool  (AbstractTool* _tool);
    static void setThickness   (size_t _thickness);
    static void setAcitveColor (Color _color);
    
    static AbstractTool* getActiveTool  ();
    static size_t        getThickness   ();
    static Color         getAcitveColor ();
    

};