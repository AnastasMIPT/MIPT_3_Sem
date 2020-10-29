#ifndef BUTTON_H
#define BUTTON_H

#include "Sorts.h"
#include "../MyLib/MyInteger.h"

#include "Primitives.h"
#include "window.h"


using MyType = Numeric<int>;

template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;


template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);



Vector<MyType> rand_vector (size_t size);

template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size = 10, size_t delta = 10, size_t max_size = 100);


template <typename T>
class SortDrawFunctor {
    CoordinatePlane* coord_plane_ass;
    CoordinatePlane* coord_plane_comp;
    SortFunc_t<T> func_sort;
    
public:
    SortDrawFunctor (CoordinatePlane* _coord_plane_ass, CoordinatePlane* _coord_plane_comp, SortFunc_t<T> _func_sort);

    void operator() ();

};



template <typename Functor_t>
class Button : public QuadWindow {
public:
    Functor_t MouseClick;
    template <typename ...Args_t>
    Button (double _x, double _y, double _size_x, double _size_y, const Color& _color, Args_t&&... args) 
    : QuadWindow (_x, _y, _size_x, _size_y, _color), MouseClick (std::forward<Args_t> (args)...) {}

    bool onMouseClick (const MouseClickEvent& event) override;
    ~Button () final = default;
};



template <typename T>
void SortDrawFunctor<T>::operator() () {
        
        
        printf ("Hello I'm functor\n");
        
        Vector<Vector<size_t>> result = CompGraph_of_sort (func_sort);
        
        Vector <Point2d> points_assigns (result.size ());
        Vector <Point2d> points_comp (result.size ());
        
        for (size_t i = 0; i < result.size (); ++i) {
                points_assigns[i].x = static_cast <double> (result[i][0]);
                points_assigns[i].y = static_cast <double> (result[i][1]);

                points_comp[i].x = static_cast <double> (result[i][0]);
                points_comp[i].y = static_cast <double> (result[i][2]);
        }
        coord_plane_ass->add_graph_by_p_arr (points_assigns);
        coord_plane_comp->add_graph_by_p_arr (points_comp);
}

template<typename T>
SortDrawFunctor<T>::SortDrawFunctor (CoordinatePlane* _coord_plane_ass, CoordinatePlane* _coord_plane_comp, SortFunc_t<T> _func_sort)
    : coord_plane_ass (_coord_plane_ass), coord_plane_comp (_coord_plane_comp), func_sort (_func_sort) {}



template <typename Functor_t>
bool Button<Functor_t>::onMouseClick (const MouseClickEvent& event) {

    printf ("Зашел в onClick кнопки\n");
    bool is_consumed = false;
     
    printf ("пытаюсь поглатить\n");
        
    is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false;
    printf ("поглатил\n");

    bool lbutton_down = false;
    if (event.button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == event.action)
            lbutton_down = true;
         else if (GLFW_RELEASE == event.action)
            lbutton_down = false;
    }

    if(lbutton_down) {
        printf ("Hello\n");
        MouseClick ();
    }

    return true;
}










template <typename T>
Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size, size_t delta, size_t max_size) {
    size_t size = start_size;
    Vector<Vector<size_t>> result;
    while (size <= max_size)
    {
        Vector<MyType> arr (rand_vector (size));

        func_sort (&arr[0], 0, size);

        Vector<size_t> temp (3);
        temp[0] = size;
        temp[1] = MyType::num_of_comp ();
        temp[2] = MyType::num_of_assigns ();
        result.push_back (temp);
        
        MyType::num_of_comp_to_zero ();
        MyType::num_of_assigns_to_zero ();
        
        size += delta;
    }
    
    return result;
}



Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = rand () % 1024;
    }
    return vec;
}

#endif // BUTTON_H