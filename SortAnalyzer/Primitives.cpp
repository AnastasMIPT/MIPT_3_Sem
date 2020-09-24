
#define DEBUG_ASSERT
#include "../MyLib/debug_assert.h"

#include "Primitives.h"


double Len_of_vec (const glm::highp_vec2& vec) {
    return sqrt (vec[0] * vec[0] + vec[1] * vec[1]);
}


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

    for (int i = 0; i < points.size (); ++i) {
        points[i].draw ();
    }
}


Arrow::Arrow (GLdouble _x1, GLdouble _y1, GLdouble _x2, GLdouble _y2) : x1 (_x1), y1 (_y1), x2 (_x2), y2 (_y2) {}

void Arrow::draw () {

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
            
            //glColor3f (0.0, 0.0, 1.0);
            glVertex2d (r_x, r_y);
            
            //glColor3f (0.0, 1.0, 0.0);
            glVertex2d (x2, y2);
    glEnd ();


    glBegin (GL_LINE_STRIP);
            glColor3f (0.0, 0.0, 0.0);
            glVertex2d (x1, y1);
            glVertex2d (x2, y2);
    glEnd ();
}




Rect::Rect (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord) 
    : size_x (_size_x), size_y (_size_y), coord (_coord) {}

void Rect::draw () const {
    glBegin (GL_QUADS);
        glColor3f (1.f, 1.f, 1.f);
        Point2d (coord.x, coord.y).draw ();
        Point2d (coord.x, coord.y + size_y).draw ();
        Point2d (coord.x + size_x, coord.y + size_y).draw ();
        Point2d (coord.x + size_x, coord.y).draw ();
    glEnd ();
}




Graph::Graph (GLdouble _size_x, GLdouble _size_y, const Point2d& _coord,
              const Vector<GLdouble>& _vec_x, const Vector<GLdouble>& _vec_y) 
    : size_x (_size_x), size_y (_size_y), coord (_coord), vec_x (_vec_x), vec_y (_vec_y) {
        im_x = coord.x + 0.015 * size_x;
        im_y = coord.y + 0.015 * size_y;
        im_size_y = (1 - 2 * off_image) * size_y;
        im_size_x = (1 - 2 * off_image) * size_x;
        
}


void Graph::draw () {


    //glClear (GL_COLOR_BUFFER_BIT);

    Rect (size_x, size_y, coord).draw ();

    Arrow OY (im_x, im_y, 
              im_x, im_y + im_size_y);
    OY.draw ();

    Arrow OX (im_x, im_y, 
              im_x + im_size_x, im_y);
    OX.draw ();

    GLdouble max_x = vec_x[vec_x.max_element ()];
    GLdouble max_y = vec_y[vec_y.max_element ()];


    glBegin (GL_LINE_STRIP);
    
    glColor3f (0.0, 1.0, 0.0);

    for (int i = 0; i < vec_x.size (); ++i) {
        glVertex2d (im_x + vec_x[i] * im_size_x / max_x, im_y + vec_y[i] * im_size_y / max_y);
    }   

    glEnd ();

}