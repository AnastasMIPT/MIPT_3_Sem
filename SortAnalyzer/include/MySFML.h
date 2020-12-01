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
    sf::Font font;

    int width  = 0;
    int height = 0;
    SFML (int width, int height, const char* name);
public:

    static std::queue<std::unique_ptr<Event>> event_que;


    void drawRect (const Rect& rect) override;
    void drawLine (const Line& line) override;
    void drawTriangle (const Triangle& triangele) override;
    void drawLineStrip (const Vector<Point2d>& points, const Color& color) override;
    
    void drawText (const std::string& _text, const Point2d& pos, int character_size = 24);

    Point2d convertAbstrToRealCoords (const Point2d& abstract_coords);
    Point2d convertRealToAbstrCoords (const Point2d& real_coords);
    Rect convertAbstrToRealRect (const Rect& abstract_rect);
    Rect convertRealToAbstrRect (const Rect& real_rect);

    int convertHorizontalSizeToPixels (double size);
    int convertVerticalSizeToPixels   (double size);
    
    double convertPixelsToHorizontalSize (int size);
    double convertPixelsToVerticalSize   (int size);
    

    bool checkCoordsInRect (double pos_x, double pos_y, const Rect& rect);

    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;
    void clear ();

    void EventConvert (sf::Event& sf_event, Event& my_event);
    int  ButtonConvert (sf::Mouse::Button button);
    sf::Color ConvertColor (const Color& color);

    friend Engine<SFML>;
    ~SFML ();
};

#endif // MYSFML_H