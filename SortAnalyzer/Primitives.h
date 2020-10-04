
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


struct Color {
    GLdouble red   = 1.0;
    GLdouble green = 1.0;
    GLdouble blue  = 1.0;

    Color () {}
    Color (GLdouble _red, GLdouble _green, GLdouble _blue);
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
    Color color;

public:
    Rect (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord, Color _color = Color ());
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
    CoordinatePlane& coord_plane_ass;
    CoordinatePlane& coord_plane_comp;
    SortFunc_t<T> func_sort;
    
public:
    SortDrawFunctor (CoordinatePlane& _coord_plane_ass, CoordinatePlane& _coord_plane_comp, SortFunc_t<T> _func_sort);

    void operator () () {
        printf ("Hello I'm functor\n");
        Vector<Vector<size_t>> result = CompGraph_of_sort (func_sort);
        
        Vector <Point2d> points_assigns (result.size ());
        Vector <Point2d> points_comp (result.size ());
        
        for (int i = 0; i < result.size (); ++i) {
                points_assigns[i].x = result[i][0];
                points_assigns[i].y = result[i][1];

                points_comp[i].x = result[i][0];
                points_comp[i].y = result[i][2];
        }
        
        coord_plane_ass.add_graph_by_p_arr (points_assigns);
        coord_plane_comp.add_graph_by_p_arr (points_comp);

    }

};


template<typename T>
SortDrawFunctor<T>::SortDrawFunctor (CoordinatePlane& _coord_plane_ass, CoordinatePlane& _coord_plane_comp, SortFunc_t<T> _func_sort)
    : coord_plane_ass (_coord_plane_ass), coord_plane_comp (_coord_plane_comp), func_sort (_func_sort) {}



template <typename Functor_t>
class Button {
    Rect background;
public:
    Functor_t action;

    template <typename ...Args_t>
    Button (GLdouble size_x, GLdouble size_y, const Point2d& coord, const Color& color, Args_t&&... args) 
    : action (std::forward<Args_t> (args)...), background (size_x, size_y, coord, color) {}

    void draw () const;
};



template <typename Functor_t>
void Button<Functor_t>::draw () const {
    background.draw ();
}

#endif // PRIMITIVES_H
