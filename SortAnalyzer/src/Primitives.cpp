
#define DEBUG_ASSERT
#include "../MyLib/debug_assert.h"

#define DEBUG
#include "../MyLib/debug_info.h"

#include "Primitives.h"
#include "button.h"
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




CoordinatePlane::CoordinatePlane (const Rect& _trappings) 
    : AbstractWindow (_trappings) {
        im_x = _trappings.coords.x + off_image * _trappings.width;
        im_y = _trappings.coords.y + off_image * _trappings.height;
        im_size_y = (1 - 2 * off_image) * _trappings.height;
        im_size_x = (1 - 2 * off_image) * _trappings.width;
        
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

    GEngine::system.drawRect (trappings);
    
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
    // if (arrow_up->CheckCoordinate (event.pos_x, event.pos_y)) {
    //     ArrowUpMouseClick (event);
    // } else if (arrow_down->CheckCoordinate (event.pos_x, event.pos_y)) {
    //     ArrowDownMouseClick (event);
    // }
    if (is_consumed) printf ("&& передал подокну");
    if (!is_consumed) {
        printf ("Hello\n");
    }
    //
    //
    return true;
}

void ScrollBar::ArrowUpMouseClick (const MouseClickEvent& event) {
    bool lbutton_down = false;
    if (event.button == MouseButtonTypes::LEFT) {
        if(MouseButtonActions::PRESS == event.action)
            lbutton_down = true;
         else if (MouseButtonActions::RELEASE == event.action)
            lbutton_down = false;
    }

    Color temp = arrow_up->trappings.color;
    if (lbutton_down) {
        arrow_up->trappings.color = COLORS::BLACK;
    } else {
        arrow_up->trappings.color = but_color;
    }
}

void ScrollBar::ArrowDownMouseClick (const MouseClickEvent& event) {
    bool lbutton_down = false;
    if (event.button == MouseButtonTypes::LEFT) {
        if(MouseButtonActions::PRESS == event.action)
            lbutton_down = true;
         else if (MouseButtonActions::RELEASE == event.action)
            lbutton_down = false;
    }

    
    if (lbutton_down) {
        arrow_down->trappings.color = COLORS::BLACK;
    } else {
        arrow_down->trappings.color = but_color;
    }
}



ScrollBar::ScrollBar (IScrollableWindow* _scroll_window, const Rect& _trappings)
: WindowContainer (_trappings),
  scroll_window (_scroll_window),
  arrow_up (new Button<ScrollFunctor> ({{_trappings.coords.x, _trappings.coords.y + _trappings.height - but_size}, 
                                       _trappings.width, but_size, but_color}, 
                                       _scroll_window, but_color, true)),

  slider (new Slider ({{_trappings.coords.x, _trappings.coords.y + _trappings.height - slider_size - but_size}, 
                      _trappings.width, /*(size_x - 2 * but_size) * scroll_window->getRatio ()*/slider_size, slider_color}, 
                       _trappings.coords.y + _trappings.height - but_size, _trappings.coords.y + but_size)),

  arrow_down (new ::Button<ScrollFunctor>  ({{_trappings.coords.x, _trappings.coords.y}, _trappings.width, but_size, but_color},
                                             _scroll_window, but_color, false)) {

    subwindows.push_back (arrow_up.get ());
    subwindows.push_back (slider.get ()); 
    subwindows.push_back (arrow_down.get ());
}


Slider::Slider (const Rect& _trappings, double _limit_up, 
                double _limit_down)
    : AbstractDragableWindow (_trappings),
      limit_up (_limit_up), limit_down (_limit_down) {}

void Slider::move (double posx, double posy) {
    double new_y = posy - off_y;
    printf ("move: pos_x = %lf, pos_y = %lf, new_y = %lf\n", posx, posy, new_y);
    if (limit_down < new_y && new_y + trappings.height < limit_up) {
        printf ("yes\n");
        trappings.coords.y = new_y;
    }
}