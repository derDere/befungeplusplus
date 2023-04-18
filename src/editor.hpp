#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "matrix.hpp"
#include "point.hpp"

using namespace std;

class Editor {
  private:
    Matrix* matrix;

  public:
    Point* position;

    Editor(Matrix*);
    ~Editor();
};

#endif
