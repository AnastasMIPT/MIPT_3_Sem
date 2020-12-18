#ifndef MYSFML_H
#define MYSFML_H


#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <queue>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "engine.h"
#include "events.h"
#include "view_port.h"
#include "window_size.h"

#include "image.h"

class SFML : IEngine {
private:
    sf::RenderWindow window;
    sf::Font font;

    std::map<size_t, sf::Texture> images;

    //std::unordered_map<int, sf::RectangleShape> rects;

    int width  = 0;
    int height = 0;
    size_t cur_image_id = 1;

    SFML (int width, int height, const char* name);
public:

    inline static std::queue<std::unique_ptr<Event>> event_que;


    void drawRect (const Rect& rect) override;
    void drawLine (const Line& line) override;
    void drawTriangle (const Triangle& triangele) override;
    void drawLineStrip (const Vector<Point2d>& points, const Color& color) override;
    
    void drawImage (const Rect& area, const Image& img);

    void drawImageInArea (const Rect& area, const Image& img, bool no_distortion = false,
            const ViewPort& view = ViewPort {0, 0, WindowWidth, WindowHeight});

    // unsigned int constructRectForFastDraw (const Rect& rect);
    // void drawRectFast (unsigned int id);

    void drawText (const std::string& _text, const Rect& pos, int character_size = 24);

    Point2d convertAbstrToRealCoords (const Point2d& abstract_coords);
    Point2d convertRealToAbstrCoords (const Point2d& real_coords);
    Rect convertAbstrToRealRect (const Rect& abstract_rect);
    Rect convertRealToAbstrRect (const Rect& real_rect);

    int convertHorizontalSizeToPixels (double size);
    int convertVerticalSizeToPixels   (double size);
    
    double convertPixelsToHorizontalSize (int size);
    double convertPixelsToVerticalSize   (int size);
    
    Image loadImageFromFile (const char* path);


    bool checkCoordsInRect (double pos_x, double pos_y, const Rect& rect);

    std::unique_ptr<Event> pollEvent () override;
    bool shouldClose () override;
    void clear ();

    void EventConvert (sf::Event& sf_event, Event& my_event);
    int  ButtonConvert (sf::Mouse::Button button);
    sf::Color ConvertColor (const Color& color);

    sf::RenderWindow* _getSfWindow ();

    friend Engine<SFML>;
    ~SFML ();
};

#endif // MYSFML_H