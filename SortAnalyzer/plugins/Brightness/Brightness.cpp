#include "Brightness.h"

bool Brightness::init() {
    properties[PluginAPI::TYPE::PRIMARY_COLOR].display_type =
        PluginAPI::Property::DISPLAY_TYPE::COLOR_PICKER;
    return true;
}

bool Brightness::deinit() { return true; }

void Brightness::start_apply(PluginAPI::Canvas canvas,
                              PluginAPI::Position pos) {
    for (int64_t i = 0; i < canvas.height * canvas.width * sizeof(int32_t);
         i += 4) {
        BrightnessPlugin::Color* current_pixel =
            reinterpret_cast<BrightnessPlugin::Color*>(canvas.pixels + i);

        BrightnessPlugin::Color* filter_color =
            reinterpret_cast<BrightnessPlugin::Color*>(
                &properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value);

        current_pixel->r = std::min (255, current_pixel->r + filter_color->r);
        current_pixel->g = std::min (255, current_pixel->g + filter_color->r);
        current_pixel->b = std::min (255, current_pixel->b + filter_color->r);
        current_pixel->a = filter_color->a;
    }
}

void Brightness::stop_apply(PluginAPI::Canvas canvas,
                             PluginAPI::Position pos) {}

void Brightness::apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {}

extern "C" PluginAPI::Plugin* get_plugin() {
    return PluginAPI::get_instance<Brightness>();
}