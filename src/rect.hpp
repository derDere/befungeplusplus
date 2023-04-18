#ifndef RECT_HPP
#define RECT_HPP

#include "point.hpp"
#include "size.hpp"

class Rect : public Point, public Size {
  public:
    Rect(int, int, int, int);
    Rect();
    ~Rect();
};

#endif
