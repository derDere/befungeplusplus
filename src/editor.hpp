#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "matrix.hpp"
#include "point.hpp"
#include "rect.hpp"

using namespace std;

class Editor {
  private:
    Matrix* matrix;
    bool strMode;

  public:
    Point* position;
    Point* direction;
    Rect* selection;

    Editor(Matrix*);
    ~Editor();

    void Inject(int);
};

#endif
