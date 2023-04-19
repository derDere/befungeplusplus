#ifndef EDITOR_CPP
#define EDITOR_CPP

#include <ncursesw/ncurses.h>

#include "editor.hpp"

using namespace std;

Editor::Editor(Matrix* matrix) {
  this->matrix = matrix;
  this->position = new Point(0, 0);
  this->direction = new Point(1, 0);
  this->strMode = false;
}

Editor::~Editor() {
  this->strMode = false;
  delete this->matrix;
  delete this->position;
  delete this->direction;
}

void Editor::Inject(int input) {
  if ((input >= ' ') && (input <= '~')) {
    this->matrix->Set(*(this->position), input);

    switch (input)
    {
      case 'v':
          this->direction->Set(DOWN);
        break;
      case '^':
          this->direction->Set(UP);
        break;
      case '<':
          this->direction->Set(LEFT);
        break;
      case '>':
          this->direction->Set(RIGHT);
        break;
    }

    this->position->Add(this->direction);

  } else if (input == KEY_BACKSPACE) {
    this->position->Sub(this->direction);
    this->matrix->Set(*(this->position), ' ');

  } else if (input == KEY_DC) {
    this->matrix->Set(*(this->position), ' ');

  } else if (input == KEY_UP) {
    this->position->MvUp();
  } else if (input == KEY_LEFT) {
    this->position->MvLeft();
  } else if (input == KEY_RIGHT) {
    this->position->MvRight();
  } else if (input == KEY_DOWN) {
    this->position->MvDown();
  }
}

#endif
