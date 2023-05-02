#ifndef EDITOR_CPP
#define EDITOR_CPP

#include <iostream>
#include <ncursesw/ncurses.h>

#include "editor.hpp"
#include "advkeys.hpp"
#include "clipboard.hpp"

using namespace std;

Editor::Editor(Matrix* matrix) {
  this->matrix = matrix;
  this->position = new Point(0, 0);
  this->direction = new Point(1, 0);
  this->selection = new Size(1, 1);
  this->strMode = false;
  this->codeView = nullptr;
}

Editor::~Editor() {
  this->strMode = false;
  delete this->matrix;
  delete this->position;
  delete this->direction;
  delete this->selection;
}

void Editor::SetCodeView(CodeView* codeView) {
  this->codeView = codeView;
}

void Editor::MouseInject(MEVENT event) {
  if (event.bstate & BUTTON1_CLICKED) { // Left click
      // Set the position to the mouse position
      this->position->X(event.x - this->codeView->bounds->X() + this->codeView->viewX());
      this->position->Y(event.y - this->codeView->bounds->Y() + this->codeView->viewY());
      this->selection->Width(1);
      this->selection->Height(1);

  } else if (event.bstate & BUTTON3_CLICKED) { // Right click
      cout << "Right click" << endl;

  } else if (event.bstate & BUTTON2_CLICKED) { // Middle click
      cout << "Middle click" << endl;

  } else if (event.bstate & BUTTON4_PRESSED) { // Mouse wheel up
      this->position->MvUp();

  } else if (event.bstate & BUTTON5_PRESSED) { // Mouse wheel down
      this->position->MvDown();
  }
}

void Editor::Inject(int input) {
  bool changedSelection = false;
  if (input == KEY_CHOME) {
    this->position->X(this->matrix->StartX());
  } else if (input == KEY_CEND) {
    this->position->X(this->matrix->StartX() + this->matrix->Width());
  } else if (input == KEY_CPPAGE) {
    this->position->Y(this->matrix->StartY());
  } else if (input == KEY_CNPAGE) {
    this->position->Y(this->matrix->StartY() + this->matrix->Height());

  } else if (input == KEY_HOME) {
    this->position->X(this->codeView->viewX() + this->codeView->viewMarginX());
  } else if (input == KEY_END) {
    this->position->X(this->codeView->viewX() + this->codeView->viewMarginX() + this->codeView->viewWidth() - 1);
  } else if (input == KEY_PPAGE) {
    this->position->Y(this->codeView->viewY() + this->codeView->viewMarginY());
  } else if (input == KEY_NPAGE) {
    this->position->Y(this->codeView->viewY() + this->codeView->viewMarginY() + this->codeView->viewHeight() - 1);

  } else if (input == KEY_BACKSPACE) {
    this->position->Sub(this->direction);
    this->matrix->Set(*(this->position), ' ');

  } else if (input == KEY_DC) {
    for (int y = 0; y < this->selection->Height(); y++) {
      for (int x = 0; x < this->selection->Width(); x++) {
        Point pos(this->position->X() + x, this->position->Y() + y);
        this->matrix->Set(pos, ' ');
      }
    }

  } else if (input == KEY_UP) {
    this->position->MvUp();
  } else if (input == KEY_LEFT) {
    this->position->MvLeft();
  } else if (input == KEY_RIGHT) {
    this->position->MvRight();
  } else if (input == KEY_DOWN) {
    this->position->MvDown();

  } else if (input == KEY_CTRL_Z) {
    Point newPos;
    if (this->matrix->Undo(newPos)) {
      this->position->X(newPos.X());
      this->position->Y(newPos.Y());
    }

  } else if (input == KEY_CTRL_Y) {
    Point newPos;
    if (this->matrix->Redo(newPos)) {
      this->position->X(newPos.X());
      this->position->Y(newPos.Y());
    }

  } else if (input == KEY_CTRL_C) {
    Rect* rect = new Rect(this->position->X(), this->position->Y(), this->selection->Width(), this->selection->Height());
    string data = this->matrix->Export(rect);
    Clipboard::SetText(data);
    delete rect;
    changedSelection = true;

  } else if (input == KEY_CTRL_X) {
    Rect* rect = new Rect(this->position->X(), this->position->Y(), this->selection->Width(), this->selection->Height());
    string data = this->matrix->Export(rect);
    Clipboard::SetText(data);
    for (int y = 0; y < rect->Height(); y++) {
      for (int x = 0; x < rect->Width(); x++) {
        this->matrix->Set({rect->X() + x, rect->Y() + y}, ' ');
      }
    }
    delete rect;

  } else if (input == KEY_CTRL_V) {
    string data = Clipboard::GetText();
    this->matrix->Import(data, this->position);
    // sets the with to the length of the longest line
    int width = 0;
    int i = 0;
    while (i < data.length()) {
      int j = 0;
      while (data[i + j] != '\n' && i + j < data.length()) {
        j++;
      }
      if (j > width) {
        width = j;
      }
      i += j + 1;
    }
    this->selection->Width(width);
    this->selection->Height(count(data.begin(), data.end(), '\n') + 1);
    changedSelection = true;

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
    this->position->MvUp();
    this->selection->Height(this->selection->Height() + 1);
    changedSelection = true;
  } else if (input == KEY_SDOWN) {
    this->selection->Height(this->selection->Height() + 1);
    changedSelection = true;
  } else if (input == KEY_SLEFT) {
    this->position->MvLeft();
    this->selection->Width(this->selection->Width() + 1);
    changedSelection = true;
  } else if (input == KEY_SRIGHT) {
    this->selection->Width(this->selection->Width() + 1);
    changedSelection = true;

  } else if (input == KEY_ENTER) {
    this->position->MvDown();
    this->position->X(0);

  } else if (input == KEY_CTRL_T) {
    this->codeView->showCross = !this->codeView->showCross;

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

  } else if (input == '\t') {
    for (int i = 0; i < 4; i++) {
      this->matrix->Set(*(this->position), ' ');
      this->position->Add(this->direction);
    }

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
  if (this->position->X() < 0) {
    this->position->X(0);
  }
  if (this->position->Y() < 0) {
    this->position->Y(0);
  }
  if (!changedSelection) {
    this->selection->Width(1);
    this->selection->Height(1);
  }
}

#endif
