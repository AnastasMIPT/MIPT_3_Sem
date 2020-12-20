#ifndef PLUGIN_H
#define PLUGIN_H

#include "../api/api.hpp"
#include "tools.h"
#include "canvas.h"
#include <string>


class Plugin : public AbstractTool {
    void* dl_handler;
    PluginAPI::Plugin* api_plug;
    PluginAPI::Position api_pos;
    PluginAPI::Canvas api_canvas;

public:
    Plugin (const std::string& name);

    void startApplying (Canvas* canvas, double x, double y) override;
    void apply (Canvas* canvas, double x, double y) override;
    void finishApplying (Canvas* canvas, double x, double y) override;

    ~Plugin ();
};


#endif // PLUGIN_H