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

    // virtual Point2d convertAbstrToRealCoords (const Point2d& abstract_coords) = 0;
    // virtual Point2d convertRealToAbstrCoords (const Point2d& real_coords)     = 0;
    // virtual Rect convertAbstrToRealRect (const Rect& abstract_rect)  = 0;
    // virtual Rect convertRealToAbstrRect (const Rect& real_rect)      = 0;

    virtual bool checkCoordsInRect (double pos_x, double pos_y, const Rect& rect) = 0;


    virtual std::unique_ptr<Event> pollEvent () = 0;
    virtual bool shouldClose () = 0;
    virtual void clear () = 0;
    


    virtual ~IEngine () = default;
};


template <typename IEngineImpl>
class Engine {
public:
    static IEngineImpl system;
};


#endif // ENGINE_H