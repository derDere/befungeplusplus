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
  if (input == KEY_BACKSPACE) {
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

  } else if (input == KEY_SLEFT) {
    this->matrix->Set(*(this->position), '<');
    this->direction->Set(LEFT);

  } else if (input == KEY_SRIGHT) {
    this->matrix->Set(*(this->position), '>');
    this->direction->Set(RIGHT);

  // } else if (input == Shift(KEY_UP) /*KEY_SUP*/) {
  //   this->matrix->Set(*(this->position), '^');
  //   this->direction->Set(UP);
  //
  // } else if (input == Shift(KEY_DOWN) /*KEY_SDOWN*/) {
  //   this->matrix->Set(*(this->position), 'v');
  //   this->direction->Set(DOWN);

  } else if (input == KEY_ENTER) {
  } else if (input == KEY_F(1)) {
  } else if (input == KEY_F(2)) {
  } else if (input == KEY_F(3)) {
  } else if (input == KEY_F(4)) {
  } else if (input == KEY_F(5)) {
  } else if (input == KEY_F(6)) {
  } else if (input == KEY_F(7)) {
  } else if (input == KEY_F(8)) {
  } else if (input == KEY_F(9)) {
  } else if (input == KEY_F(10)) {
  } else if (input == KEY_F(11)) {
  } else if (input == KEY_F(12)) {

  } else if ((input >= 32) && (input <= 126)) { // between space and ~
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
  }
}

#endif
