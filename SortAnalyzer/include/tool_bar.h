#ifndef TOOL_BAR_H
#define TOOL_BAR_H
#include "tools.h"
#include "window.h"
#include "tool_manger.h"
#include <vector>
#include <memory>


class ToolBar : public WindowContainer {
    static constexpr double top_off  = 0.1;
    static constexpr double left_off = 0.1;
    

    std::vector <AbstractTool*> tools;

public:
    
    ToolBar (const Rect& _trappings);
    ~ToolBar ();
 //   AbstractTool* getToolById (size_t id);


    // TO DO functor, that  trow event, when instrument selected

};


#endif // TOOL_BAR_H