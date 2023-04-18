#ifndef EDITOR_CPP
#define EDITOR_CPP

#include "editor.hpp"

using namespace std;

Editor::Editor(Matrix* matrix) {
  this->matrix = matrix;
  this->position = new Point(0, 0);
}

Editor::~Editor() {
  delete this->matrix;
  delete this->position;
}

#endif
