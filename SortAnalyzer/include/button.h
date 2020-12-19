#ifndef BUTTON_H
#define BUTTON_H

#include "Sorts.h"
#include "MyInteger.h"
//#include "Primitives.h"
#include "window.h"
#include "tools.h"
#include "image_pool.h"
#include "scrollable_windows.h"

using MyType = Numeric<int>;



template <typename T>
using SortFunc_t = void (*) (T*, size_t, size_t);



Vector<MyType> rand_vector (size_t size);

// template <typename T>
// Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size = 10, size_t delta = 10, size_t max_size = 100);




// template <typename T>
// Vector<Vector<size_t>> CompGraph_of_sort (SortFunc_t<T> func_sort, size_t start_size, size_t delta, size_t max_size) {
//     size_t size = start_size;
//     Vector<Vector<size_t>> result;
//     while (size <= max_size)
//     {
//         Vector<MyType> arr (rand_vector (size));

//         func_sort (&arr[0], 0, size);

//         Vector<size_t> temp (3);
//         temp[0] = size;
//         temp[1] = MyType::num_of_comp ();
//         temp[2] = MyType::num_of_assigns ();
//         result.push_back (temp);
        
//         MyType::num_of_comp_to_zero ();
//         MyType::num_of_assigns_to_zero ();
        
//         size += delta;
//     }
    
//     return result;
// }






template <typename ButtonFunctor_t>
class Button : public AbstractWindow {
    bool lbutton_down = false;
    Color default_color;
    Image* image = NULL;
public:
    ButtonFunctor_t MousePress;
    template <typename ...Args_t>
    Button (const Rect& _trappings, Args_t&&... args) 
    : AbstractWindow (_trappings), default_color (trappings.color), MousePress (std::forward<Args_t> (args)...) {}

    void setImage (Image* _image) {
        image = _image;
    }


    void draw () const override {
        AbstractWindow::draw ();
        if (image) {
           GEngine::system.drawImageInArea (trappings, *image, true);
        }
    }
    bool onMouseClick (const MouseClickEvent& event) override;
    ~Button () final = default;
};



class EmptyFunctor {
public:
    void operator() (Button<EmptyFunctor>* _but, const MouseClickEvent& event) 
    {printf ("*****************I'm release functor\n");}
};







class  ScrollFunctor {
    IScrollableWindow* scroll_window;
    Color color;
    bool scroll_up;
public:
    ScrollFunctor (IScrollableWindow* _scroll_window, const Color& _color, bool _scroll_up)
    : scroll_window (_scroll_window), color (_color), scroll_up (_scroll_up) {}
    void operator() (Button<ScrollFunctor>* _but, const MouseClickEvent& event);
};


class ToolFunctor {
    size_t tool_id;
public:
    ToolFunctor (size_t _tool_id) : tool_id (_tool_id) {}
    void operator() (Button<ToolFunctor>* _but, const MouseClickEvent& event);
};














// template <typename T>
// class SortDrawFunctor {
//     CoordinatePlane* coord_plane_ass;
//     CoordinatePlane* coord_plane_comp;
//     SortFunc_t<T> func_sort;
    
// public:
//     SortDrawFunctor (CoordinatePlane* _coord_plane_ass, CoordinatePlane* _coord_plane_comp, SortFunc_t<T> _func_sort);

//     void operator() (Button<SortDrawFunctor<T>>* but, const MouseClickEvent& event);

// };



// template <typename T>
// void SortDrawFunctor<T>::operator() (Button<SortDrawFunctor<T>>* but, const MouseClickEvent& event) {
        
//     bool lbutton_down = false;
//     if (event.button == MouseButtonTypes::LEFT) {
//         if(MouseButtonActions::PRESS == event.action)
//             lbutton_down = true;
//         else if (MouseButtonActions::RELEASE == event.action)
//             lbutton_down = false;
//     }
//     printf ("Hello I'm functor\n");
    
//     if (lbutton_down) {
//         Vector<Vector<size_t>> result = CompGraph_of_sort (func_sort);
    
//         Vector <Point2d> points_assigns (result.size ());
//         Vector <Point2d> points_comp (result.size ());
        
//         for (size_t i = 0; i < result.size (); ++i) {
//                 points_assigns[i].x = static_cast <double> (result[i][0]);
//                 points_assigns[i].y = static_cast <double> (result[i][1]);

//                 points_comp[i].x = static_cast <double> (result[i][0]);
//                 points_comp[i].y = static_cast <double> (result[i][2]);
//         }
//         coord_plane_ass->add_graph_by_p_arr (points_assigns);
//         coord_plane_comp->add_graph_by_p_arr (points_comp);
//     }
// }

// template<typename T>
// SortDrawFunctor<T>::SortDrawFunctor (CoordinatePlane* _coord_plane_ass, CoordinatePlane* _coord_plane_comp, SortFunc_t<T> _func_sort)
//     : coord_plane_ass (_coord_plane_ass), coord_plane_comp (_coord_plane_comp), func_sort (_func_sort) {}



template <typename ButtonFunctor_t>
bool Button<ButtonFunctor_t>::onMouseClick (const MouseClickEvent& event) {

    printf ("Зашел в onClick кнопки\n");
    // bool is_consumed = false;
     
    // printf ("пытаюсь поглотить\n");
        
    bool our_coords = CheckCoordinate (event.pos_x, event.pos_y);
    // if (!is_consumed) return false;
    // printf ("поглатил\n");

    lbutton_down = false;
    if (event.button == MouseButtonTypes::LEFT) {
        if(MouseButtonActions::PRESS == event.action)
            lbutton_down = true;
         else if (MouseButtonActions::RELEASE == event.action)
            lbutton_down = false;
    }

    if (lbutton_down) {
        if (our_coords) {
            printf ("***** our_coords+ldown\n");
            trappings.color -= COLORS::DEFAULT_BLACOUT;
            return true;
        }
    } else {
        trappings.color = default_color;
        if (our_coords) {
            MousePress (this, event);
            printf ("***** our_coords+lrelease\n");
            return true;
        }
    }
    printf ("****lrelease + othercoords\n");
    return false;
}





template <typename ButtonFunctor_t>
class ImageButton : public Button<ButtonFunctor_t> {
    
};


#endif // BUTTON_H