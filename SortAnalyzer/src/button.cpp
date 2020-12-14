#include "button.h"

template<>
size_t Numeric<int>::num_assigns = 0;

template<>
size_t Numeric<int>::num_comparisons = 0;

void ScrollFunctor::operator() (Button<ScrollFunctor>* _but, const MouseClickEvent& event) {
    if (scroll_up) 
        scroll_window->scrollOnceUp ();
    else
        scroll_window->scrollOnceDown ();
}


void ToolFunctor::operator() (Button<ToolFunctor>* _but, const MouseClickEvent& event) {
    _but->setImage (ImagePool::getImageById (tool_id + TOOLS::TOOLS_COUNT));
}








Vector<MyType> rand_vector (size_t size) {
    Vector<MyType> vec (size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = rand () % 1024;
    }
    return vec;
}