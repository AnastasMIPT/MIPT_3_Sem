#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdio>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../MyLib/my_vector.h"


class Point2d {
public:
    GLdouble x;
    GLdouble y;

    Point2d (GLdouble _x, GLdouble _y);

    Point2d (const Point2d& other);

    void draw () const;
};

class Arrow {
    GLdouble x1;
    GLdouble y1;
    GLdouble x2;
    GLdouble y2;
    static constexpr double tip_width = 0.010;
    static constexpr double tip_height = 0.05;
public:
    Arrow (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
    void draw ();
};


class Rect {
    GLdouble size_x;
    GLdouble size_y;
    Point2d coord;

public:
    Rect (GLdouble _size_x, GLdouble _size_y, const Point2d& coord);
    void draw () const;
};



class Graph {
    GLdouble size_x;
    GLdouble size_y;
    Point2d coord;
    GLdouble image_x;
    GLdouble image_y;

    const Vector<GLdouble>& vec_x;
    const Vector<GLdouble>& vec_y;

public:

    Graph (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord,
    const Vector<GLdouble>& _vec_x, const Vector<GLdouble>& _vec_y);
    void draw ();
};


#endif // PRIMITIVES_H
