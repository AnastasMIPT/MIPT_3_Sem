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
class Button : public AbstractWindow {
    Rect background;
    Functor_t MouseClick;
public:

    template <typename ...Args_t>
    Button (GLdouble size_x, GLdouble size_y, const Point2d& coord, const Color& color, Args_t&&... args) 
    : background (size_x, size_y, coord, color), MouseClick (std::forward<Args_t> (args)...) {}

    void draw () const override;
    void onMouseClick () override;
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
    background.draw ();
}


template <typename Functor_t>
void Button<Functor_t>::onMouseClick () {
  
}


#endif // BUTTON_H