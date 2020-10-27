
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



#include "window.h"


const double DefaultMaxVal = -228;


double Len_of_vec (const glm::highp_vec2& vec);



class Point2d {
public:
    double x;
    double y;

    Point2d (double _x, double _y);

    Point2d (const Point2d& other);

    Point2d () = default;

    void draw () const;

   ~Point2d ()   = default;
};


struct Color   {
    double red   = 1.0;
    double green = 1.0;
    double blue  = 1.0;

    Color () = default;
    Color (double _red, double _green, double _blue);
    void draw () const;

    ~Color ()   = default;
};


class Arrow {
    double x1;
    double y1;
    double x2;
    double y2;
    static constexpr double tip_width = 0.010;
    static constexpr double tip_height = 0.05;
public:
    Arrow (double x1, double y1, double x2, double y2);
    void draw () const   ;

    ~Arrow ()   = default;
};


class Rect   {
    double x;
    double y;
    double size_x;
    double size_y;
    Color color;

public:
    Rect (double _x, double _y, double _size_x, double _size_y, Color _color = Color ());
    void draw () const   ;

    ~Rect ()   = default;
};

class LineStrip   {
    const Vector<Point2d>& points;
public:
    LineStrip (const Vector<Point2d>& _points);
    void draw () const   ;

    ~LineStrip ()   = default;
}; 


class Graph   {
    double im_x;
    double im_y;
    double im_size_x;
    double im_size_y;
    
    Vector<Point2d> points;

    double max_x;
    double max_y;
    

public:
    Graph (double _im_x, double _im_y, double _im_size_x, double _im_size_y,
           const Vector<Point2d>& _points, double _max_x , double _max_y);

    Graph (double _im_x, double _im_y, double _im_size_x, double _im_size_y,
           const Vector<Point2d>& _points);


    void change_max_x (double _max_x);
    void change_max_y (double _max_y);
    void draw () const     ;
    ~Graph ()   = default;
};


class QuadWindow : public IWindow {
public:
    double x;
    double y;
    double size_x;
    double size_y;
    Color color;
public:
    QuadWindow (double _x, double _y, double _size_x, double _size_y);
    bool CheckCoordinate (double pos_x, double pos_y) const;
    bool onMouseClick (const MouseClickEvent& event) {}
    void draw () const {
        glBegin (GL_QUADS);
            color.draw ();
            Point2d (x, y).draw ();
            Point2d (x, y + size_y).draw ();
            Point2d (x + size_x, y + size_y).draw ();
            Point2d (x + size_x, y).draw ();
        glEnd ();
    }

    ~QuadWindow () = default;
};



class CoordinatePlane : public QuadWindow {
    double im_size_x;
    double im_size_y;
    double im_x;
    double im_y;
    static constexpr double off_image = 0.03;

    Vector<Graph> graphs;

public:

    CoordinatePlane (double _x, double _y,double _size_x, double _size_y);
    
    void add_graph_by_p_arr (const Vector<Point2d>& points);
    void draw_graphs () const;
    void draw () const;

    ~CoordinatePlane ()   = default;
};



size_t Ind_of_point_with_max_x (const Vector<Point2d>& points);
size_t Ind_of_point_with_max_y (const Vector<Point2d>& points);


#endif // PRIMITIVES_H
