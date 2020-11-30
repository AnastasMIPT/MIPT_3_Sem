
#define DEBUG
#include "../../MyLib/debug_info.h"
#include "window.h"
#include "application.h"

void WindowContainer::addWindow (IWindow* window) {
    subwindows.push_back (window);
}

void WindowContainer::draw () const {
    GEngine::system.drawRect (trappings);
    for (auto window : subwindows) {
        window->draw ();
    }
}

bool WindowContainer::onMouseClick (const MouseClickEvent& event) {
    printf ("Принял событие\n");
    DEB_INFO
    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    printf ("is_consumed = %d\n", is_consumed);
    if (!is_consumed) {
        printf ("у события неверные координаты: %lf, %lf\n", event.pos_x, event.pos_y);
        printf ("Координаты контейнера %lf, %lf, размеры: %lf, %lf\n", trappings.coords.x, trappings.coords.y,
        trappings.width, trappings.height);
        return false;
    }
    DEB_INFO
    printf ("у события нужные координаты\n");
    printf ("Координаты контейнера %lf, %lf\n", trappings.coords.x, trappings.coords.y);
    for (auto window : subwindows) {
        is_consumed = window->onMouseClick (event);
        if (is_consumed) printf ("Приняло подокно с координатами y = %lf\n",
                                 dynamic_cast<AbstractWindow*> (window)->trappings.coords.y);
        if (is_consumed) return true;
    }

    printf ("событие не поглощено\n");

    return false;
}


WindowContainer::WindowContainer (const Rect& _trappings)
: AbstractWindow (_trappings) {}

AbstractWindow::AbstractWindow (const Rect& _trappings)
: trappings (_trappings) {}


void AbstractWindow::draw () const {
    GEngine::system.drawRect (trappings);
}

bool AbstractWindow::CheckCoordinate (double pos_x, double pos_y) const {
    double w_x = trappings.coords.x;
    double w_y = trappings.coords.y;
    
    printf ("Проверяю координаты входящие: %lf, %lf. Координаты кнопки %lf, %lf размеы: %lf, %lf\n",
    pos_x, pos_y, w_x, w_y, trappings.width, trappings.height);
    fflush (stdin);
    if (!((pos_x > w_x) && (pos_y > w_y) && (pos_x < w_x + trappings.width) && (pos_y < w_y + trappings.height))) printf ("Координаты не подходят\n");
    return pos_x > w_x && pos_y > w_y && pos_x < w_x + trappings.width && pos_y < w_y + trappings.height? true : false;
    //return GEngine::system.checkCoordsInRect (pos_x, pos_y, trappings);
}

bool AbstractWindow::onMouseClick (const MouseClickEvent& event) {
    DEB_INFO
    bool is_consumed = CheckCoordinate (event.pos_x, event.pos_y);
    if (!is_consumed) return false;
    DEB_INFO
    printf ("Я квадратное окно, на меня нажали, мои координаты:" 
            "%lf, %lf, col_r = %lf, col_g = %lf, col_b = %lf\n", 
            trappings.coords.x, trappings.coords.y, 
            trappings.color.red, trappings.color.green, trappings.color.blue);
    return true;
}


bool AbstractDragableWindow::onMouseClick (const MouseClickEvent& event) {
    DEB_INFO
    if (event.button == MouseButtonTypes::LEFT) {
        if(MouseButtonActions::PRESS == event.action && CheckCoordinate (event.pos_x, event.pos_y)) {
            is_drag = true;
            off_x = event.pos_x - trappings.coords.x;
            off_y = event.pos_y - trappings.coords.y;
            trappings.color.red -= 0.2;
            trappings.color.green -= 0.2;
            trappings.color.blue -= 0.2;
            Application::setActiveWindow (this); 
            return true;
        }
        else if (MouseButtonActions::RELEASE == event.action && is_drag) {
            DEB_INFO
            is_drag = false;
            trappings.color.red += 0.2;
            trappings.color.green += 0.2;
            trappings.color.blue += 0.2;
            Application::setActiveWindow (NULL);
        }
    }
    return false;
}

void AbstractDragableWindow::onMouseMove (const MouseMoveEvent& event) {
    //DEB_INFO
    printf ("event.pos_y = %lf\n", event.pos_y);
    move (event.pos_x, event.pos_y);
}


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