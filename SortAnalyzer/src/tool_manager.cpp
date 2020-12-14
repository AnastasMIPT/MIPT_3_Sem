#include "tool_manager.h"


void ToolManager::setActiveTool (size_t tool_id) {
    active_tool = tool_id;
}

void ToolManager::setAcitveColor (Color _color) {
    active_color = _color;
}

void ToolManager::setThickness (size_t _thickness) {
    thickness = _thickness;
}

AbstractTool* ToolManager::getActiveTool () {
    return tools[active_tool];
}

size_t ToolManager::getThickness () {
    return thickness;
}

Color ToolManager::getAcitveColor () {
    return active_color;
}

void ToolManager::setActiveToolBut  (Button<ToolFunctor>* but) {
    active_tool_but = but;
}

Button<ToolFunctor>* ToolManager::getAcitveToolBut  () {
    return active_tool_but;
}

size_t ToolManager::getActiveToolId () {
    return active_tool;
}