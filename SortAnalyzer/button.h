#ifndef BUTTON_H
#define BUTTON_H


#include "Primitives.h"
#include "window.h"

template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);


template <typename T>
class SortDrawFunctor {
    CoordinatePlane& coord_plane_ass;
    CoordinatePlane& coord_plane_comp;
    SortFunc_t<T> func_sort;
    
public:
    SortDrawFunctor (CoordinatePlane& _coord_plane_ass, CoordinatePlane& _coord_plane_comp, SortFunc_t<T> _func_sort);

    void operator() ();

};


template <typename Functor_t>
class Button : public QuadWindow {
public:
    Color color;
    Functor_t MouseClick;
    template <typename ...Args_t>
    Button (double _x, double _y, double _size_x, double _size_y, const Color& _color, Args_t&&... args) 
    : QuadWindow (_x, _y, _size_x, _size_y), color (_color), MouseClick (std::forward<Args_t> (args)...) {}

    void draw () const override;
    void onMouseClick (MouseClickEvent* event) override;
    ~Button () final = default;
};



template <typename T>
void SortDrawFunctor<T>::operator() () {
        
        
        printf ("Hello I'm functor\n");
        
        Vector<Vector<size_t>> result = CompGraph_of_sort (func_sort);
        
        Vector <Point2d> points_assigns (result.size ());
        Vector <Point2d> points_comp (result.size ());
        
        for (size_t i = 0; i < result.size (); ++i) {
                points_assigns[i].x = result[i][0];
                points_assigns[i].y = result[i][1];

                points_comp[i].x = result[i][0];
                points_comp[i].y = result[i][2];
        }
        coord_plane_ass.add_graph_by_p_arr (points_assigns);
        coord_plane_comp.add_graph_by_p_arr (points_comp);
}

template<typename T>
SortDrawFunctor<T>::SortDrawFunctor (CoordinatePlane& _coord_plane_ass, CoordinatePlane& _coord_plane_comp, SortFunc_t<T> _func_sort)
    : coord_plane_ass (_coord_plane_ass), coord_plane_comp (_coord_plane_comp), func_sort (_func_sort) {}



template <typename Functor_t>
void Button<Functor_t>::draw () const {
    Rect (x, y, x_size, y_size, color).draw ();
}


template <typename Functor_t>
void Button<Functor_t>::onMouseClick (MouseClickEvent* event) {
    bool lbutton_down = false;
    if (event->button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == event->action)
            lbutton_down = true;
         else if (GLFW_RELEASE == event->action)
            lbutton_down = false;
    }

    if(lbutton_down) {
        printf ("Hello\n");
        //MouseClick ();
    }
}


#endif // BUTTON_H