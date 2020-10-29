
#define DEBUG_ASSERT
#include "../MyLib/debug_assert.h"

#define DEBUG
#include "../MyLib/debug_info.h"

#include "Primitives.h"

double Len_of_vec (const glm::highp_vec2& vec) {
    return sqrt (vec[0] * vec[0] + vec[1] * vec[1]);
}

size_t Ind_of_point_with_max_x (const Vector<Point2d>& points) {
    size_t ind = 0;
    double max_x = points[0].x;
    for (size_t i = 1; i < points.size (); ++i) {
        if (points[i].x > max_x) {
            ind = i;
            max_x = points[i].x;
        }
    }  
    return ind;
}

size_t Ind_of_point_with_max_y (const Vector<Point2d>& points) {
    size_t ind = 0;
    double max_y = points[0].y;
    for (size_t i = 1; i < points.size (); ++i) {
        if (points[i].y > max_y) {
            ind = i;
            max_y = points[i].y;
        }
    }
    return ind;
}


Arrow::Arrow (double _x1, double _y1, double _x2, double _y2) : x1 (_x1), y1 (_y1), x2 (_x2), y2 (_y2) {}

void Arrow::draw () const {

    glm::highp_vec2 base (x2 - x1, y2- y1);
    base *= (Len_of_vec (base) - tip_height) / Len_of_vec (base);
    glm::highp_vec2 right  (base[1], -base[0]);
    right /= Len_of_vec (right);
    right *= tip_width / 2;

    double r_x = x1 + base[0] + right[0];
    double r_y = y1 + base[1] + right[1];
    double l_x = x1 + base[0] - right[0];
    double l_y = y1 + base[1] - right[1];

    GEngine::system.drawTriangle ({{l_x, l_y}, {r_x, r_y}, {x2, y2}, {0, 0, 0}});
    GEngine::system.drawLine ({{x1, y1}, {x2, y2}, {0, 0, 0}});
}




CoordinatePlane::CoordinatePlane (double _x, double _y, double _size_x, double _size_y) 
    : QuadWindow (_x, _y, _size_x, _size_y) {
        im_x = x + off_image * size_x;
        im_y = y + off_image * size_y;
        im_size_y = (1 - 2 * off_image) * size_y;
        im_size_x = (1 - 2 * off_image) * size_x;
        
}

void CoordinatePlane::draw_graphs () const {
    for (size_t i = 0; i < graphs.size (); ++i) {
        
        graphs[i].draw ();
    }
}


void CoordinatePlane::add_graph_by_p_arr (const Vector<Point2d>& points) {
    graphs.push_back (Graph (im_x, im_y, im_size_x, im_size_y, points));
}

void CoordinatePlane::draw () const {

    GEngine::system.drawRect ({{x, y}, size_x, size_y});
    
    Arrow OY (im_x, im_y, im_x, im_y + im_size_y);
    OY.draw ();

    Arrow OX (im_x, im_y, im_x + im_size_x, im_y);
    OX.draw ();

    draw_graphs ();
}


Graph::Graph (double _im_x, double _im_y, double _im_size_x, double _im_size_y,
           const Vector<Point2d>& _points, double _max_x, double _max_y) 
    
    : im_x (_im_x), im_y (_im_y), im_size_x (_im_size_x), im_size_y (_im_size_y), 
      points (_points), max_x (_max_x), max_y (_max_y) {}


Graph::Graph (double _im_x, double _im_y, double _im_size_x, double _im_size_y,
           const Vector<Point2d>& _points) 
    
    : im_x (_im_x), im_y (_im_y), im_size_x (_im_size_x), im_size_y (_im_size_y), 
      points (_points) {
    DEB_INFO
    max_x = points[Ind_of_point_with_max_x (points)].x;
    max_y = points[Ind_of_point_with_max_y (points)].y;
    DEB_INFO
   
}


void Graph::draw () const {
    Vector<Point2d> temp_points (points);
    for (int i = 0; i < temp_points.size (); ++i) {
        temp_points[i].x = im_x + points[i].x * im_size_x / max_x;
        temp_points[i].y = im_y + points[i].y * im_size_y / max_y;
    }
    GEngine::system.drawLineStrip (temp_points, {0, 1, 0});
}

void Graph::change_max_x (double _max_x) {
    max_x = _max_x;
}

void Graph::change_max_y (double _max_y) {

    max_y = _max_y;
}

bool ScrollBar::onMouseClick (const MouseClickEvent& event) {
    DEB_INFO
    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false; 
    DEB_INFO
    is_consumed = WindowContainer::onMouseClick (event);
    if (is_consumed) printf ("&& передал подокну");
    if (!is_consumed) {
        printf ("Hello\n");
    }
    //
    //
    return true;
}

ScrollBar::ScrollBar (double _x, double _y, double _size_x, double _size_y, const Color& _color)
: WindowContainer (_x, _y, _size_x, _size_y, _color), 
  arrow_up (new ::QuadWindow (_x, _y + _size_y - 0.1, _size_x, 0.1, {0, 0.5, 1})),
  slider (new ::QuadWindow (_x, _y + 0.1, _size_x, 0.2, {0.6, 0.5, 1})),
  arrow_down (new ::QuadWindow (_x, _y, _size_x, 0.1, {0, 0.5, 1})) {
    subwindows.push_back (arrow_up.get ());
    subwindows.push_back (slider.get ()); 
    subwindows.push_back (arrow_down.get ());
}