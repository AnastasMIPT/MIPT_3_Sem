#include "scrollable_windows.h"
#include <stdio.h>


AbstractScrollableWindow::AbstractScrollableWindow (int _num_of_units, int _num_of_visable_units)
: num_of_units (_num_of_units), num_of_visable_units (_num_of_visable_units) {}


double AbstractScrollableWindow::getRatio (bool is_vertical) {
    return static_cast<double> (num_of_visable_units) / num_of_units;
}


void AbstractScrollableWindow::scrollOnceUp (bool is_vertical) {
    if (num_of_first_unit - 1 >= 0) num_of_first_unit--;
    printf ("nunit = %d\n", num_of_first_unit);

}


void AbstractScrollableWindow::scrollOnceDown (bool is_vertical) {
    if (num_of_first_unit + 1 < num_of_units - num_of_visable_units) num_of_first_unit++;
    printf ("nunit = %d\n", num_of_first_unit);
}

void AbstractScrollableWindow::slideByRatio (double ratio, bool is_vertical) {
    num_of_first_unit = ratio * (num_of_units - num_of_visable_units);
    printf ("nunit = %d\n", num_of_first_unit);
}