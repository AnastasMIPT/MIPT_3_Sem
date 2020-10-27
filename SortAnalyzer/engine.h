#ifndef ENGINE_H
#define ENGINE_H
#include <cstdio>

class IEngine {
public:
    virtual void drawRect () = 0;
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