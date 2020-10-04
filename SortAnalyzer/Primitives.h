#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdio>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../MyLib/my_vector.h"


const GLdouble DefaultMaxVal = -228;

template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);





double Len_of_vec (const glm::highp_vec2& vec);

class Point2d {
public:
    GLdouble x;
    GLdouble y;

    Point2d (GLdouble _x, GLdouble _y);

    Point2d (const Point2d& other);

    Point2d () = default;

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

class LineStrip {
    const Vector<Point2d>& points;
public:
    LineStrip (const Vector<Point2d>& _points);
    void draw () const;

}; 


class Graph {
    GLdouble im_size_x;
    GLdouble im_size_y;
    GLdouble im_x;
    GLdouble im_y;
    GLdouble max_x;
    GLdouble max_y;
    Vector<Point2d> points;

public:
    Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points, GLdouble _max_x , GLdouble _max_y);

    Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points);


    void change_max_x (GLdouble _max_x);
    void change_max_y (GLdouble _max_y);
    void draw ();
};


class CoordinatePlane {
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
    void draw_graphs ();
    void draw ();
};





int Ind_of_point_with_max_x (const Vector<Point2d>& points);
int Ind_of_point_with_max_y (const Vector<Point2d>& points);



template <typename T>
class SortDrawFunctor {
    const CoordinatePlane& coord_plane;
    SortFunc_t<T> func_sort;
    
public:
    SortDrawFunctor (const CoordinatePlane& _coord_plane, SortFunc_t<T> _func_sort);

    void operator () () {
        printf ("Hello I'm functor\n");

    }

};


template<typename T>
SortDrawFunctor<T>::SortDrawFunctor (const CoordinatePlane& _coord_plane, SortFunc_t<T> _func_sort)
    : coord_plane (_coord_plane), func_sort (_func_sort) {}



template <typename Functor_t>
class Button {
public:
    Functor_t action;

    template <typename ...Args_t>
    Button (Args_t&&... args) : action (std::forward<Args_t> (args)...) {}
};


#endif // PRIMITIVES_H
