#ifndef ENGINE_H
#define ENGINE_H
#include <cstdio>
#include <memory>
#include "events.h"
#include "color.h"
#include "../MyLib/my_vector.h"

using namespace ab;

class IEngine {
public:
    virtual void drawRect (const Rect& rect) = 0;
    virtual void drawLine (const Line& line) = 0;
    virtual void drawTriangle (const Triangle& triangele) = 0;    
    virtual void drawLineStrip (const Vector<Point2d>& points, const Color& color) = 0;

    virtual bool checkCoordsInRect (double pos_x, double pos_y, const Rect& rect) = 0;

    // virtual unsigned int constructRectForFastDraw (const Rect& rect) = 0;
    // virtual void drawRectFast (unsigned int id) = 0;

    virtual std::unique_ptr<Event> pollEvent () = 0;
    virtual bool shouldClose () = 0;
    virtual void clear () = 0;
    


    virtual ~IEngine () = default;
};


template <typename IEngineImpl>
class Engine {
    ~Engine () = default;
public:
    static IEngineImpl system;
};


#endif // ENGINE_H