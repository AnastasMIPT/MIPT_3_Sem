#include "tool_bar.h"
#include "button.h"

ToolBar::ToolBar (const Rect& _trappings) 
: WindowContainer (_trappings) {


    for (size_t tool_id = 0; tool_id < TOOLS::TOOLS_COUNT; ++tool_id) {
        double but_h = (trappings.height - top_off * trappings.height * 2) / 2;
        double but_w = but_h / 2;
        double but_x = trappings.coords.x + left_off * trappings.width + tool_id * but_w;
        double but_y = trappings.coords.y + top_off * trappings.height + but_h;
        Button<ToolFunctor>* cur_but = 
            new Button<ToolFunctor> ({but_x, but_y, but_w, but_h, trappings.color}, tool_id);
        cur_but->setImage (ImagePool::getImageById (tool_id));
        WindowContainer::addWindow (cur_but);
        //printf ("cur_but tool = %lu\n", tool_id);
    }

    


    ToolManager::setActiveTool    (TOOLS::PENCIL);
    auto* pencil_but = dynamic_cast<Button<ToolFunctor>*> (subwindows[0]);
    ToolManager::setActiveToolBut (pencil_but);
    pencil_but->setImage (ImagePool::getImageById (TOOLS::PENCIL + TOOLS::TOOLS_COUNT));


}

ToolBar::~ToolBar () {
    for (auto ptr : subwindows) {
        delete ptr;
    }
}

