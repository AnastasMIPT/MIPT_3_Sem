#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H
#include "tools.h"
#include "window.h"
#include <vector>



class ToolManager : public WindowContainer {
    std::vector <AbstractTool*> tools;

public:
    
    ToolManager (const Rect& _trappings);
    AbstractTool* getToolById (size_t id);


    // TO DO functor, that  trow event, when instrument selected

};


#endif // TOOL_MANAGER