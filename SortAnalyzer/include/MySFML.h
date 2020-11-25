#ifndef MYSFML_H
#define MYSFML_H


#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <queue>
#include <memory>
#include "engine.h"
#include "events.h"

class SFML : IEngine {
private:
    sf::RenderWindow window;
    SFML (int width, int height, const char* name);
public:

    static std::queue<std::unique_ptr<Event>> event_que;


    void drawRect (const Rect& rect) override;
    void drawTriangle (const Triangle& triangele) override;
    void drawLine (const Line& line) override;
    void drawLineStrip (const Vector<Point2d>& points, const Color& color) override;
    void clear ();

    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;

    void EventConvert (sf::Event& sf_event, Event& my_event);
    int  ButtonConvert (sf::Mouse::Button button);


    friend Engine<SFML>;
    ~SFML () = default;
};

#endif // MYSFML_H