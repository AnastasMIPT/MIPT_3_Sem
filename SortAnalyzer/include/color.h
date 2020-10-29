#ifndef COLOR_H
#define COLOR_H

struct Color   {
    double red   = 1.0;
    double green = 1.0;
    double blue  = 1.0;
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


#endif // COLOR_H