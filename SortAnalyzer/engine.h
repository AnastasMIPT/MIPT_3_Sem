#ifndef ENGINE_H
#define ENGINE_H
#include <cstdio>
#include <memory>
#include "events.h"

class IEngine {
public:
    virtual void drawRect () = 0;
    virtual void createAppWindow (int width, int height, const char* name) = 0;
    virtual std::unique_ptr<Event> pollEvent () = 0;
    virtual bool shouldClose () = 0;

    virtual ~IEngine () = default;
};


template <typename IEngineImpl>
class Engine : IEngineImpl {
public:
    static IEngineImpl system;
};



class SFML : IEngine {
    SFML () = default;
public:
    void drawRect () {printf ("SFML rect\n");}

    friend Engine<SFML>;
};
#endif // ENGINE_H