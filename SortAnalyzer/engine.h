#ifndef ENGINE_H
#define ENGINE_H
#include <cstdio>
#include <memory>
#include "events.h"
#include "color.h"

class IEngine {
public:
    virtual void drawRect (const Rect& rect) = 0;
    virtual void drawTriangle (const Triangle& triangele) = 0;
    virtual std::unique_ptr<Event> pollEvent () = 0;
    virtual bool shouldClose () = 0;

    virtual ~IEngine () = default;
};


template <typename IEngineImpl>
class Engine {
public:
    static IEngineImpl system;
};



class SFML : IEngine {
    SFML () = default;
public:
    void drawRect (const Rect& rect) override {printf ("SFML rect\n");}

    friend Engine<SFML>;
};
#endif // ENGINE_H