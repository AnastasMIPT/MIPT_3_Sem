#include "plugin.h"
#include <dlfcn.h>
#include <memory>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


Plugin::Plugin (const std::string& name) {

    
    dl_handler  = dlopen(("./plugins/" + name + "/" + name + ".so").c_str (), RTLD_NOW);
    if (nullptr == dl_handler) {
        printf("%s\n", dlerror()); 
        exit (2);
    }

    PluginAPI::Plugin* (*get_plugin)() = 
        reinterpret_cast<PluginAPI::Plugin* (*)()>(dlsym(dl_handler, "get_plugin"));

    if (nullptr == get_plugin) {
        printf("%s\n", dlerror());
        dlclose(dl_handler);
        exit (3);
    }

    api_plug = get_plugin();
    api_plug->init();

    ImagePool::addImage (("./plugins/" + name + "/" + "icon.png").c_str ());
    
}

void Plugin::startApplying (Canvas* canvas, double x, double y) {
    api_plug->properties[PluginAPI::TYPE::THICKNESS].int_value = ToolManager::getThickness ();
    
    Color act_col = ToolManager::getAcitveColor ();
    
    api_plug->properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value = 
                            *(reinterpret_cast<int*> (&act_col));

    const Image* img = canvas->getCanvasPixels ();
    size_t im_w = img->getWidth  ();
    size_t im_h = img->getHeight ();
    uint8_t* arr = (uint8_t*) (img->getPixelArray ());
    api_canvas = {arr, im_w, im_h};
    
    
    Point2d pixel_coords = canvas->convertToCanvasCoords ({x, y});
    api_pos = {pixel_coords.x, pixel_coords.y};

    api_plug->start_apply (api_canvas, api_pos);


}

void Plugin::apply (Canvas* canvas, double x, double y) {
    Point2d pixel_coords = canvas->convertToCanvasCoords ({x, y});
    api_pos = {pixel_coords.x, pixel_coords.y};

    api_plug->apply (api_canvas, api_pos);
}


void Plugin::finishApplying (Canvas* canvas, double x, double y) {
    Point2d pixel_coords = canvas->convertToCanvasCoords ({x, y});
    api_pos = {pixel_coords.x, pixel_coords.y};

    api_plug->stop_apply (api_canvas, api_pos);
}



Plugin::~Plugin () {
    assert (api_plug);
    api_plug->deinit();
    dlclose(dl_handler);
}