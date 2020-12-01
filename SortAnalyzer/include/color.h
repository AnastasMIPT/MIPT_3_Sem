#ifndef COLOR_H
#define COLOR_H




namespace ab {

    struct Color   {
        double red   = 1.0;
        double green = 1.0;
        double blue  = 1.0;
    };

    namespace COLORS {
        constexpr Color DEFAULT_BACKGROUND {0.0, 1.0, 0.5};
        constexpr Color DEFAULT_SLIDER     {0.6, 0.6, 0.6};
        constexpr Color DEFAULT_BUTTON     {0.7, 0.7, 0.7};
        constexpr Color LIGHT_GRAY         {0.9, 0.9, 0.9};
        constexpr Color GREEN              {0.0, 1.0, 0.0};
        constexpr Color RED                {1.0, 0.0, 0.0};
        constexpr Color BLUE               {0.0, 0.0, 1.0};
        constexpr Color WHITE              {1.0, 1.0, 1.0};
        constexpr Color BLACK              {0.0, 0.0, 0.0};
        
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