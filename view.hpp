#ifndef VIEW_HPP
#define VIEW_HPP

#include "rect.hpp"
#include <ncursesw/panel.h>
#include <ncursesw/ncurses.h>

using namespace std;

class View {
  protected:
    WINDOW* win;
    PANEL* pan;

  public:
    Rect* bounds;

    View();
    ~View();

    void Reposition();
};

#endif
