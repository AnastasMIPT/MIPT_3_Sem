
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "my_vector.h"
#include "color.h"
#include "engine.h"
#include "window.h"


//#define DEBUG
#include "debug_info.h"

const double DefaultMaxVal = -228;



class Arrow {
    double x1;
    double y1;
    double x2;
    double y2;
    static constexpr double tip_width = 0.010;
    static constexpr double tip_height = 0.05;
public:
    Arrow (double x1, double y1, double x2, double y2);
    void draw () const;

    ~Arrow ()   = default;
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




class CoordinatePlane : public AbstractWindow {
    double im_size_x;
    double im_size_y;
    double im_x;
    double im_y;
    static constexpr double off_image = 0.03;

    Vector<Graph> graphs;

public:

    CoordinatePlane (const Rect& _trappings);
    
    void add_graph_by_p_arr (const Vector<Point2d>& points);
    void draw_graphs () const;
    void draw () const override;

    ~CoordinatePlane ()   = default;
};








size_t Ind_of_point_with_max_x (const Vector<Point2d>& points);
size_t Ind_of_point_with_max_y (const Vector<Point2d>& points);

double Len_of_vec (const glm::highp_vec2& vec);


#endif // PRIMITIVES_H
