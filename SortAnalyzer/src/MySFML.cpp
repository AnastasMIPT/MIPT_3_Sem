#include "MySFML.h"

std::queue <std::unique_ptr<Event>> SFML::event_que;



SFML::SFML (int width, int height, const char* name) 
    : window (sf::VideoMode (width, height), name) {}


std::unique_ptr<Event> SFML::pollEvent () {

    // glViewport (100, 0, 400, 500);
    // glBegin (GL_TRIANGLES);
    //     glColor3f (1, 0, 0);
    //     //glVertex2d (-1.2, -0.5);
    //     //glVertex2d (0.0, 0.5);
    //     //glVertex2d (0.5, -0.5);
    //     // glVertex2i (300, 300);
    //     // glVertex2i (300, 400);
    //     // glVertex2i (00, 400);
    // glEnd ();
    // glViewport (0, 0, 600, 675);

    // glfwSwapBuffers (app_window);
    // glfwPollEvents ();
    // std::unique_ptr<Event> res = std::make_unique<Event>();
    // if (!event_que.empty ()) {
    //     res = std::move (event_que.front ());
    //     event_que.pop ();
    // }
    // return res;
}


bool SFML::shouldClose () {
    return !window.isOpen ();
}

void SFML::drawRect (const Rect& rect) {
    sf::RectangleShape rec (sf::Vector2f(rect.width, rect.height));
    rec.setPosition (sf::Vector2f (rect.coords.x, rect.coords.y));
    rec.setFillColor (sf::Color(rect.color.red, rect.color.green, rect.color.blue));
    //rec.setOutlineColor (sf::Color(frgColor.red, frgColor.green, frgColor.blue, frgColor.alpha));
    //rec.setOutlineThickness (thickness);
    window.draw(rec);
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