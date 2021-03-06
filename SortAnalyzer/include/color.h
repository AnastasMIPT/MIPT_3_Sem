#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <vector>
#include "slidable.h"

namespace ab {

    struct Color   {
        double red   = 1.0;
        double green = 1.0;
        double blue  = 1.0;
        double alpha = 1.0;


        void operator-= (const Color& other) {
            red   = std::max (0.0, red   - other.red);
            green = std::max (0.0, green - other.green);
            blue  = std::max (0.0, blue  - other.blue);
        }
    };

    struct SlidableColor {
        SlidableValue<double> r = SlidableValue<double> (1.0, 1.0, 0.0);
        SlidableValue<double> g = SlidableValue<double> (1.0, 1.0, 0.0);
        SlidableValue<double> b = SlidableValue<double> (1.0, 1.0, 0.0);
        SlidableValue<double> a = SlidableValue<double> (1.0, 1.0, 0.0);

        SlidableColor () = default;

        SlidableColor (const Color& color)
        : r (color.red, 1.0, 0.0),  g (color.green, 1.0, 0.0),
          b (color.blue, 1.0, 0.0), a (color.alpha, 1.0, 1.0) {}

        Color getColor () {
            return {r.getValue (), g.getValue (), b.getValue (), a.getValue ()};
        } 
    };

    namespace COLORS {
        constexpr Color DEFAULT_BACKGROUND {1.0, 1.0, 0.7};
        constexpr Color DEFAULT_SLIDER     {0.6, 0.6, 0.6};
        constexpr Color DEFAULT_FADER_PIN  {0.65, 0.65, 0.65};
        constexpr Color DEFAULT_BUTTON     {0.7, 0.7, 0.7};
        constexpr Color LIGHT_GRAY         {0.9, 0.9, 0.9};
        constexpr Color GREEN              {0.0, 1.0, 0.0};
        constexpr Color RED                {1.0, 0.0, 0.0};
        constexpr Color BLUE               {0.0, 0.0, 1.0};
        constexpr Color WHITE              {1.0, 1.0, 1.0};
        constexpr Color BLACK              {0.0, 0.0, 0.0};
        constexpr Color TRANSPARENT        {0.0, 0.0, 0.0, 0.0};
        constexpr Color DEFAULT_TOOL_BAR   {240.0 / 255, 240.0 / 255, 240.0 / 255 };
        constexpr Color DEFAULT_TEXT       {0.0, 0.5, 0.5};

        constexpr Color DEFAULT_BLACOUT    {0.2, 0.2, 0.2};
    };

    struct Pixel {
        u_int8_t red   = 255;
        u_int8_t green = 255;
        u_int8_t blue  = 255;
        u_int8_t alpha = 255;
        
        Pixel () = default;

        Pixel (u_int8_t _red, u_int8_t _green, u_int8_t _blue, u_int8_t _alpha)
        : red (_red), green (_green), blue (_blue), alpha (_alpha) {} 
        
        Pixel (const Color& clr)
        : red (clr.red * 255), green (clr.green * 255),
          blue (clr.blue * 255), alpha (clr.alpha * 255) {} 

    };



    struct Point2d
    {
        double x;
        double y;
    };

    struct Line
    {
        Point2d first_p;
        Point2d second_p;
        Color color;
    };


    struct Triangle {
        Point2d first_p;
        Point2d second_p;
        Point2d third_p;
        Color color;
    };

    struct Rect
    {
        Point2d coords;
        double width;
        double height;
        Color color;
    };


};

#endif // COLOR_H