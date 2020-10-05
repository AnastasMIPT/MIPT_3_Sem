
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdio>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../MyLib/my_vector.h"

//#define DEBUG
#include "../MyLib/debug_info.h"

const GLdouble DefaultMaxVal = -228;


double Len_of_vec (const glm::highp_vec2& vec);


class DrawableObject {
public:
    virtual void draw () const = 0;
    virtual ~DrawableObject () = default;
};



class Point2d : public DrawableObject {
public:
    GLdouble x;
    GLdouble y;

    Point2d (GLdouble _x, GLdouble _y);

    Point2d (const Point2d& other);

    Point2d () = default;

    void draw () const final override;

   ~Point2d () final = default;
};


struct Color : public DrawableObject {
    GLdouble red   = 1.0;
    GLdouble green = 1.0;
    GLdouble blue  = 1.0;

    Color () = default;
    Color (GLdouble _red, GLdouble _green, GLdouble _blue);
    void draw () const override;

    ~Color () final = default;
};


class Arrow : DrawableObject {
    GLdouble x1;
    GLdouble y1;
    GLdouble x2;
    GLdouble y2;
    static constexpr double tip_width = 0.010;
    static constexpr double tip_height = 0.05;
public:
    Arrow (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
    void draw () const override;

    ~Arrow () final = default;
};


class Rect : public DrawableObject {
    GLdouble size_x;
    GLdouble size_y;
    Point2d coord;
    Color color;

public:
    Rect (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord, Color _color = Color ());
    void draw () const override;

    ~Rect () final = default;
};

class LineStrip : public DrawableObject {
    const Vector<Point2d>& points;
public:
    LineStrip (const Vector<Point2d>& _points);
    void draw () const override;

    ~LineStrip () final = default;
}; 


class Graph : public DrawableObject {
    GLdouble im_x;
    GLdouble im_y;
    GLdouble im_size_x;
    GLdouble im_size_y;
    
    Vector<Point2d> points;

    GLdouble max_x;
    GLdouble max_y;
    

public:
    Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points, GLdouble _max_x , GLdouble _max_y);

    Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points);


    void change_max_x (GLdouble _max_x);
    void change_max_y (GLdouble _max_y);
    void draw () const final override;
    ~Graph () final = default;
};


class CoordinatePlane : public DrawableObject {
    GLdouble size_x;
    GLdouble size_y;
    Point2d coord;
    GLdouble im_size_x;
    GLdouble im_size_y;
    GLdouble im_x;
    GLdouble im_y;
    static constexpr GLdouble off_image = 0.03;

    Vector<Graph> graphs;

public:

    CoordinatePlane (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord);
    //void add_graph (const Graph& graph);
    void add_graph_by_p_arr (const Vector<Point2d>& points);
    void draw_graphs () const;
    void draw () const final override;

    ~CoordinatePlane () final = default;
};



size_t Ind_of_point_with_max_x (const Vector<Point2d>& points);
size_t Ind_of_point_with_max_y (const Vector<Point2d>& points);


#endif // PRIMITIVES_H
