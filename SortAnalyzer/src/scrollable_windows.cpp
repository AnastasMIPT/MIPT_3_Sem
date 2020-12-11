
#include "scrollable_windows.h"
#include <stdio.h>

AbstractScrollableWindow::AbstractScrollableWindow (int _num_of_units, int _num_of_visable_units)
: num_of_units (_num_of_units), num_of_visable_units (_num_of_visable_units) {}


double AbstractScrollableWindow::getRatio () {
    return static_cast<double> (num_of_visable_units) / num_of_units;
}


void AbstractScrollableWindow::scrollOnceUp () {
    if (num_of_first_unit - 1 >= 0) num_of_first_unit--;
    printf ("nunit = %d\n", num_of_first_unit);

}


void AbstractScrollableWindow::scrollOnceDown () {
    if (num_of_first_unit + 1 < num_of_units - num_of_visable_units) num_of_first_unit++;
    printf ("nunit = %d\n", num_of_first_unit);
}