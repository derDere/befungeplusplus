#ifndef RECT_CPP
#define RECT_CPP

#include "rect.hpp"

Rect::Rect(int x, int y, int width, int height) : Point(x, y), Size(width, height) { }
Rect::Rect() : Rect(0, 0, 0, 0) { }
Rect::~Rect() { }

bool Rect::Contains(Point point) {
  return
    point.X() >= this->X() &&
    point.X() < this->X() + this->Width() &&
    point.Y() >= this->Y() &&
    point.Y() < this->Y() + this->Height();
}

#endif
