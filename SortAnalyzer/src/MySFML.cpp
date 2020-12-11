#include "MySFML.h"
#include "config.h"

// std::queue <std::unique_ptr<Event>> SFML::event_que;



SFML::SFML (int _width, int _height, const char* _name) 
    : window (sf::VideoMode (_width, _height), _name), width (_width), height (_height) {

        font.loadFromFile ("./resources/fonts/18473.ttf");
}

void SFML::clear () {
    window.clear ();
}

std::unique_ptr<Event> SFML::pollEvent () {
    
    std::unique_ptr<Event> res (new Event);
    res.get ()->type = Event::EventTypes::DEFAULT_EVENT;
    sf::Event event;
    if (!window.pollEvent (event)) {
        return res;
    }
    EventConvert (event, *res.get());
    
    window.display ();
    return res;
}

int SFML::ButtonConvert (sf::Mouse::Button button) {
    switch (button)
    {
    case sf::Mouse::Left:
            return MouseButtonTypes::LEFT;

    case sf::Mouse::Right:
        return MouseButtonTypes::RIGHT;

    case sf::Mouse::Middle:
        return MouseButtonTypes::MIDDLE;

    default:
        break;
    }
}

void SFML::EventConvert (sf::Event& sf_event, Event& my_event) {
    switch (sf_event.type)
    {
    case sf::Event::MouseButtonPressed:
    { 
        my_event.type = Event::EventTypes::MOUSE_CLICK;
        Point2d abstr_coords = convertRealToAbstrCoords ({sf_event.mouseButton.x, 
                                                          sf_event.mouseButton.y});
        my_event.ev.mouse_click = MouseClickEvent (abstr_coords.x, 
                                                   abstr_coords.y,
                                                   ButtonConvert (sf_event.mouseButton.button), 
                                                   MouseButtonActions::PRESS, 0);
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        my_event.type = Event::EventTypes::MOUSE_CLICK;
        Point2d abstr_coords = convertRealToAbstrCoords ({sf_event.mouseButton.x, 
                                                          sf_event.mouseButton.y});
        my_event.ev.mouse_click = MouseClickEvent (abstr_coords.x, 
                                                   abstr_coords.y,
                                                   ButtonConvert (sf_event.mouseButton.button), 
                                                   MouseButtonActions::RELEASE, 0);
        break;
    }
    case sf::Event::MouseMoved:
    {
        my_event.type = Event::EventTypes::MOUSE_MOVE;
        Point2d abstr_coords = convertRealToAbstrCoords ({sf_event.mouseMove.x, 
                                                          sf_event.mouseMove.y});
        
        my_event.ev.mouse_move = MouseMoveEvent (abstr_coords.x, abstr_coords.y);
        break;
    }
    case sf::Event::Closed:
        window.close ();
        break;

    default:
        break;
    }
}

SFML::~SFML () {
    window.close ();
}

bool SFML::shouldClose () {
    return !window.isOpen ();
}

sf::Color SFML::ConvertColor (const Color& color) {
    return sf::Color(color.red * 255, color.green * 255, color.blue * 255);
}

void SFML::drawRect (const Rect& _rect) {
    Rect rect = convertAbstrToRealRect (_rect);
    sf::RectangleShape rec (sf::Vector2f(rect.width, rect.height));
    rec.setPosition (sf::Vector2f (rect.coords.x, rect.coords.y - rect.height));
    rec.setFillColor (ConvertColor (rect.color));
    window.draw (rec);
}

void SFML::drawTriangle (const Triangle& triangele) {

    // glBegin (GL_TRIANGLES);
    //     glColor3f (triangele.color.red, triangele.color.green, triangele.color.blue);
    //     glVertex2d (triangele.first_p.x, triangele.first_p.y);
    //     glVertex2d (triangele.second_p.x, triangele.second_p.y);
    //     glVertex2d (triangele.third_p.x, triangele.third_p.y);
    // glEnd ();
}

void SFML::drawLine (const Line& line) {
    // glBegin (GL_LINE_STRIP);
    //         glColor3f (line.color.red, line.color.green, line.color.blue);
    //         glVertex2d (line.first_p.x, line.first_p.y);
    //         glVertex2d (line.second_p.x, line.second_p.y);
    // glEnd ();
}

void SFML::drawLineStrip (const Vector<Point2d>& points, const Color& color) {
    // glBegin (GL_LINE_STRIP);
    //     glColor3f (color.red, color.green, color.blue);
    //     for (size_t i = 0; i < points.size (); ++i) {
    //         glVertex2d (points[i].x, points[i].y);
    //     }
    // glEnd ();
}



Point2d SFML::convertAbstrToRealCoords (const Point2d& abstract_coords) {
    return Point2d {abstract_coords.x * window.getSize ().x, window.getSize ().y * (1.0 - abstract_coords.y)};
}

Point2d SFML::convertRealToAbstrCoords (const Point2d& real_coords) {
    return Point2d {real_coords.x / window.getSize ().x, 1 - real_coords.y / window.getSize ().y};
}

Rect SFML::convertAbstrToRealRect (const Rect& abstract_rect) {
    if (!window.isOpen()) {
        return {abstract_rect.coords.x * WindowWidth, WindowHeight * (1.0 - abstract_rect.coords.y), abstract_rect.width * WindowWidth,
                     1 * abstract_rect.height * WindowHeight, abstract_rect.color};
    }
    Point2d real_coord = convertAbstrToRealCoords (abstract_rect.coords);
    return {real_coord, abstract_rect.width * window.getSize ().x,
                     1 * abstract_rect.height * window.getSize ().y, abstract_rect.color};
}
    
Rect SFML::convertRealToAbstrRect (const Rect& real_rect) {
    return {};
}

bool SFML::checkCoordsInRect (double pos_x, double pos_y, const Rect& rect) {
    double rec_x = rect.coords.x;
    double rec_y = rect.coords.y;
    return pos_x > rec_x && 
           pos_y < rec_y && 
           pos_x < rec_x + rect.width && 
           pos_y > rec_y - rect.height?  true : false;
}

void SFML::drawText (const std::string& _text, const Rect& pos, int character_height) {
    sf::Text text;
    text.setFont (font);
    text.setString (_text);
    Rect real_rect = convertAbstrToRealRect (pos);
    text.setCharacterSize (character_height);
    text.setPosition (real_rect.coords.x, real_rect.coords.y - real_rect.height);
    text.setCharacterSize (character_height);
    
    window.draw (text);

}

int SFML::convertHorizontalSizeToPixels (double size) {
    return size * window.getSize ().x;
}
int SFML::convertVerticalSizeToPixels   (double size) {
    return size * window.getSize ().y;
}

double SFML::convertPixelsToHorizontalSize (int size) {
    return size / static_cast <double> (window.getSize ().x);
}

double SFML::convertPixelsToVerticalSize   (int size) {
    return size / static_cast <double> (window.getSize ().y);
}


// size_t SFML::loadTexture (const char* _path) {
//     sf::Texture texture;
//     texture.loadFromFile (_path);
//     images[cur_image_id] = std::move (texture);
//     cur_image_id++;
//     return cur_image_id - 1;
// }

Image SFML::loadImageFromFile (const char* path) {
    sf::Image sf_img;
    sf_img.loadFromFile (path);

    size_t img_width  = sf_img.getSize().x;
    size_t img_height = sf_img.getSize().y;

    std::vector<Pixel> pixels (img_width * img_height);
    for (size_t y = 0; y < img_height; ++y) {
        for (size_t x = 0; x < img_width; ++x) {
            auto sf_color = sf_img.getPixel (x, y);
            pixels[y * img_width + x] = Pixel (sf_color.r, sf_color.g, sf_color.b, sf_color.a);
        }
    }
    
    return Image (img_width, img_height, pixels); 
}

void SFML::drawImage (const Rect& area, const Image& img) {
    Rect real_area = convertAbstrToRealRect (area);
    
    sf::Texture sf_texture;
    sf_texture.create (img.getWidth (), img.getHeight ());
    sf_texture.update (reinterpret_cast<const sf::Uint8*> (img.getPixelArray ()));
    
    sf::Sprite sf_sprite;
    sf_sprite.setTexture (sf_texture);
    sf_sprite.setPosition (real_area.coords.x, real_area.coords.y - real_area.height);
    window.draw (sf_sprite);
}


void SFML::drawImageInArea (const Rect& area, const Image& img, bool no_distortion) {
    Rect real_area = convertAbstrToRealRect (area);
    
    sf::Texture sf_texture;

    size_t im_width  = img.getWidth  ();
    size_t im_height = img.getHeight ();

    sf_texture.create (im_width, im_height);
    sf_texture.update (reinterpret_cast<const sf::Uint8*> (img.getPixelArray ()));
    
    sf::Sprite sf_sprite;
    sf_sprite.setTexture (sf_texture);

    if (no_distortion) {
        double ratio_y = real_area.height / im_height;
        double ratio_x = real_area.width  / im_width;
        double res_ratio = 1.0;
        
        if (im_height * ratio_x <= real_area.height) {                 // what ratio is nearer to 1
            res_ratio = ratio_x;
            
            double centered_y = real_area.coords.y 
                                   - real_area.height / 2           // centring by y
                                   - im_height * res_ratio / 2;
            sf_sprite.setPosition (real_area.coords.x, centered_y); 
        
        } else {
            res_ratio = ratio_y;
            
            double centered_x = real_area.coords.x 
                                   + real_area.width / 2           // centring by x
                                   - im_width * res_ratio / 2;
            sf_sprite.setPosition (centered_x, real_area.coords.y - real_area.height);
        
        }

        sf_sprite.setScale (res_ratio, res_ratio); 

    } else {
        sf_sprite.setPosition (real_area.coords.x, real_area.coords.y - real_area.height);
        sf_sprite.setScale (real_area.width / im_width, real_area.height / im_height);
    }
    window.draw (sf_sprite);
}


// unsigned int SFML::constructRectForFastDraw (const Rect& _rect) {
//     Rect rect = convertAbstrToRealRect (_rect);
//     sf::RectangleShape rec (sf::Vector2f(rect.width, rect.height));
//     rec.setPosition (sf::Vector2f (rect.coords.x, rect.coords.y - rect.height));
//     rec.setFillColor (ConvertColor (rect.color));
//     rects[cur_id] = std::move (rec);
//     cur_id++;
//     return (cur_id - 1);
// }

// void SFML::drawRectFast (unsigned int id) {
//     window.draw (rects[id]);
// }

sf::RenderWindow* SFML::_getSfWindow () {
    return &window;
}