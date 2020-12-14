#include "tool_manger.h"


void ToolManager::setActiveTool (AbstractTool* _tool) {
    active_tool = _tool;
}

void ToolManager::setAcitveColor (Color _color) {
    active_color = _color;
}

void ToolManager::setThickness (size_t _thickness) {
    thickness = _thickness;
}

AbstractTool* ToolManager::getActiveTool () {
    return active_tool;
}

size_t ToolManager::getThickness () {
    return thickness;
}

Color ToolManager::getAcitveColor () {
    return active_color;
}