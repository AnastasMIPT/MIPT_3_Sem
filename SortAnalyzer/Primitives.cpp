#include <cstdio>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


#define DEBUG_ASSERT
#include "../MyLib/debug_assert.h"

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

double Len_of_vec (const glm::highp_vec2& vec) {
    return sqrt (vec[0] * vec[0] + vec[1] * vec[1]);
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

class Graph {
    GLdouble size_x;
    GLdouble size_y;
    GLdouble object_x;
    GLdouble object_y;
    GLdouble image_x;
    GLdouble image_y;

    const Vector<GLdouble>& vec_x;
    const Vector<GLdouble>& vec_y;

public:

    Graph (GLdouble _size_x, GLdouble _size_y, GLdouble _object_x, GLdouble _object_y, 
    const Vector<GLdouble>& vec_x, const Vector<GLdouble>& vec_y);
    void draw ();
};


Graph::Graph (GLdouble _size_x, GLdouble _size_y, GLdouble _object_x, GLdouble _object_y,
              const Vector<GLdouble>& _vec_x, const Vector<GLdouble>& _vec_y) 
    : size_x (_size_x), size_y (_size_y), object_x (_object_x), object_y (_object_y), vec_x (_vec_x), vec_y (_vec_y) {}


void Graph::draw () {


    //glClear (GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f (1.f, 1.f, 1.f);
        glVertex2d (object_x, object_y);
        glVertex2d (object_x, object_y + size_y);
        glVertex2d (object_x + size_x, object_y + size_y);
        glVertex2d (object_x + size_x, object_y);
    glEnd();

    Arrow OY (object_x + 0.008 + 0.010 / 2, object_y + size_y - 0.008 - 0.05 - 0.92, 
              object_x + 0.008 + 0.010 / 2, object_y + size_y - 0.008);
    OY.draw ();

    Arrow OX (object_x + 0.008 + 0.010 / 2, object_y + size_y - 0.008 - 0.05 - 0.92, 
              object_x + size_x -0.01, object_y + size_y - 0.008 - 0.05 - 0.92);
    OX.draw ();

    glBegin (GL_LINE_STRIP);
    
    glColor3f (0.0, 1.0, 0.0);
    

    GLdouble max_x = vec_x[vec_x.max_element ()];
    GLdouble max_y = vec_y[vec_y.max_element ()];


    for (int i = 0; i < vec_x.size (); ++i) {
        glVertex2d (object_x + vec_x[i] / max_x, object_y + vec_y[i] / max_y);
    }

    glEnd ();


}