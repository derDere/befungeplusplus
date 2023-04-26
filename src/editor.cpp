#ifndef EDITOR_CPP
#define EDITOR_CPP

#include <iostream>
#include <ncursesw/ncurses.h>

#include "editor.hpp"

#define KEY_SUP 337
#define KEY_SDOWN 336

#define KEY_CLEFT 546
#define KEY_CRIGHT 561
#define KEY_CUP 547
#define KEY_CDOWN 526

#define KEY_ALEFT 544
#define KEY_ARIGHT 559
#define KEY_AUP 565
#define KEY_ADOWN 524

#define KEY_POS1 262
#define KEY_END_DE 360

using namespace std;

Editor::Editor(Matrix* matrix) {
  this->matrix = matrix;
  this->position = new Point(0, 0);
  this->direction = new Point(1, 0);
  this->strMode = false;
  this->codeView = nullptr;
}

Editor::~Editor() {
  this->strMode = false;
  delete this->matrix;
  delete this->position;
  delete this->direction;
}

void Editor::SetCodeView(CodeView* codeView) {
  this->codeView = codeView;
}

void Editor::Inject(int input) {
  if (input == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      this->position->X(event.x - this->codeView->bounds->X() + this->codeView->viewX());
      this->position->Y(event.y - this->codeView->bounds->Y() + this->codeView->viewY());
    }

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

  } else if (input == KEY_ALEFT) {
    this->matrix->Set(*(this->position), '<');
    this->direction->Set(LEFT);
    this->position->MvLeft();
  } else if (input == KEY_ARIGHT) {
    this->matrix->Set(*(this->position), '>');
    this->direction->Set(RIGHT);
    this->position->MvRight();
  } else if (input == KEY_AUP) {
    this->matrix->Set(*(this->position), '^');
    this->direction->Set(UP);
    this->position->MvUp();
  } else if (input == KEY_ADOWN) {
    this->matrix->Set(*(this->position), 'v');
    this->direction->Set(DOWN);
    this->position->MvDown();

  } else if (input == KEY_CLEFT) {
    this->direction->Set(LEFT);
  } else if (input == KEY_CRIGHT) {
    this->direction->Set(RIGHT);
  } else if (input == KEY_CUP) {
    this->direction->Set(UP);
  } else if (input == KEY_CDOWN) {
    this->direction->Set(DOWN);

  } else if (input == KEY_SUP) {
  } else if (input == KEY_SDOWN) {
  } else if (input == KEY_SLEFT) {
  } else if (input == KEY_SRIGHT) {

  } else if (input == KEY_POS1 || input == KEY_HOME) { // TODO: KEY_HOME is not working
    this->position->X(0);
  } else if (input == KEY_END_DE || input == KEY_END) { // TODO: KEY_END is not working
    this->position->X(this->matrix->Width());
  } else if (input == KEY_PPAGE) {
    this->position->Y(0);
  } else if (input == KEY_NPAGE) {
    this->position->Y(this->matrix->Height());

  } else if (input == KEY_ENTER) {
    this->position->MvDown();
    this->position->X(0);

  } else if (input == KEY_F(1)) {
  } else if (input == KEY_F(2)) {
  } else if (input == KEY_F(3)) {
  } else if (input == KEY_F(4)) {
  } else if (input == KEY_F(5)) {
    // TODO: Run
  } else if (input == KEY_F(6)) {
  } else if (input == KEY_F(7)) {
  } else if (input == KEY_F(8)) {
  } else if (input == KEY_F(9)) {
    // TODO: Stop
  } else if (input == KEY_F(10)) {
  } else if (input == KEY_F(11)) {
    // TODO: Step
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
      case '|':
          this->direction->Set(UP);
        break;
      case '_':
          this->direction->Set(LEFT);
    }
    this->position->Add(this->direction);
  }
  else {
    cout << "input: " << input << endl;
  }
}

#endif
