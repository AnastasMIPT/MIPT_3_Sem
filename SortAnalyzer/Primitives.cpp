
#define DEBUG_ASSERT
#include "../MyLib/debug_assert.h"



//#define DEBUG
#include "../MyLib/debug_info.h"

#include "Primitives.h"


double Len_of_vec (const glm::highp_vec2& vec) {
    return sqrt (vec[0] * vec[0] + vec[1] * vec[1]);
}

size_t Ind_of_point_with_max_x (const Vector<Point2d>& points) {
    size_t ind = 0;
    GLdouble max_x = points[0].x;
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
    GLdouble max_y = points[0].y;
    for (size_t i = 1; i < points.size (); ++i) {
        if (points[i].y > max_y) {
            ind = i;
            max_y = points[i].y;
        }
    }
    return ind;
}


void Color::draw () const {
    glColor3d (red, green, blue);
}

Color::Color (GLdouble _red, GLdouble _green, GLdouble _blue) : red (_red), green (_green), blue (_blue) {}

Point2d::Point2d (GLdouble _x, GLdouble _y)
    : x (_x), y (_y) {}

Point2d::Point2d (const Point2d& other) 
    : x (other.x), y (other.y) {}

void Point2d::draw () const {
    glVertex2d (x, y);
}


LineStrip::LineStrip (const Vector<Point2d>& _points) : points (_points) {}

void LineStrip::draw () const {

    glBegin (GL_LINE_STRIP);
    glColor3f (0.0, 1.0, 0.0);

    for (size_t i = 0; i < points.size (); ++i) {
        points[i].draw ();
    }
}


Arrow::Arrow (GLdouble _x1, GLdouble _y1, GLdouble _x2, GLdouble _y2) : x1 (_x1), y1 (_y1), x2 (_x2), y2 (_y2) {}

void Arrow::draw () const {

    glm::highp_vec2 base (x2 - x1, y2- y1);
    base *= (Len_of_vec (base) - tip_height) / Len_of_vec (base);
    glm::highp_vec2 right  (base[1], -base[0]);
    right /= Len_of_vec (right);
    right *= tip_width / 2;

    GLdouble r_x = x1 + base[0] + right[0];
    GLdouble r_y = y1 + base[1] + right[1];
    GLdouble l_x = x1 + base[0] - right[0];
    GLdouble l_y = y1 + base[1] - right[1];

    // printf ("%lf\n", sqrt (right[0] * right[0] + right[1] * right[1]));

    glBegin (GL_TRIANGLES);
            glColor3f (0.0, 0.0, 0.0);
            glVertex2d (l_x, l_y);
            glVertex2d (r_x, r_y);
            glVertex2d (x2, y2);
    glEnd ();

    glBegin (GL_LINE_STRIP);
            glColor3f (0.0, 0.0, 0.0);
            glVertex2d (x1, y1);
            glVertex2d (x2, y2);
    glEnd ();
}



Rect::Rect (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord, Color _color) 
    : size_x (_size_x), size_y (_size_y), coord (_coord), color (_color) {}

void Rect::draw () const {
    glBegin (GL_QUADS);
        color.draw ();
        Point2d (coord.x, coord.y).draw ();
        Point2d (coord.x, coord.y + size_y).draw ();
        Point2d (coord.x + size_x, coord.y + size_y).draw ();
        Point2d (coord.x + size_x, coord.y).draw ();
    glEnd ();
}




CoordinatePlane::CoordinatePlane (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord) 
    : size_x (_size_x), size_y (_size_y), coord (_coord) {
        im_x = coord.x + off_image * size_x;
        im_y = coord.y + off_image * size_y;
        im_size_y = (1 - 2 * off_image) * size_y;
        im_size_x = (1 - 2 * off_image) * size_x;
        
}

void CoordinatePlane::draw_graphs () const {
    for (size_t i = 0; i < graphs.size (); ++i) {
        graphs[i].draw ();
    }
}

// void CoordinatePlane::add_graph (const Graph& graph) {
//     graphs.push_back (graph);
// }

void CoordinatePlane::add_graph_by_p_arr (const Vector<Point2d>& points) {
    DEB_INFO
    graphs.push_back (Graph (im_x, im_y, im_size_x, im_size_y, points));
    DEB_INFO
    DEB_INFO
}

void CoordinatePlane::draw () const {

    Rect (size_x, size_y, coord).draw ();

    Arrow OY (im_x, im_y, im_x, im_y + im_size_y);
    OY.draw ();

    Arrow OX (im_x, im_y, im_x + im_size_x, im_y);
    OX.draw ();

    draw_graphs ();
}


Graph::Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points, GLdouble _max_x, GLdouble _max_y) 
    
    : im_x (_im_x), im_y (_im_y), im_size_x (_im_size_x), im_size_y (_im_size_y), 
      points (_points), max_x (_max_x), max_y (_max_y) {}


Graph::Graph (GLdouble _im_x, GLdouble _im_y, GLdouble _im_size_x, GLdouble _im_size_y,
           const Vector<Point2d>& _points) 
    
    : im_x (_im_x), im_y (_im_y), im_size_x (_im_size_x), im_size_y (_im_size_y), 
      points (_points) {
    DEB_INFO
    max_x = points[Ind_of_point_with_max_x (points)].x;
    max_y = points[Ind_of_point_with_max_y (points)].y;
    DEB_INFO
   
}


void Graph::draw () const {

    glBegin (GL_LINE_STRIP);
    glColor3d (0.0, 1.0, 0.0);
    for (size_t i = 0; i < points.size (); ++i) {
        glVertex2d (im_x + points[i].x * im_size_x / max_x, im_y + points[i].y * im_size_y / max_y);
    }   
    glEnd ();
}

void Graph::change_max_x (GLdouble _max_x) {
    max_x = _max_x;
}

void Graph::change_max_y (GLdouble _max_y) {
    max_y = _max_y;
}


