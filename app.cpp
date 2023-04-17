#ifndef APP_CPP
#define APP_CPP

#include "app.hpp"

using namespace std;
using namespace BefungePlusPlus;

App::App() {
  this->borderPos = 0.75;
  this->horizontal = true;
  this->showCode = true;
  this->editMode = false;
  this->editStrMode = false;
  this->asciiMode = false;
}

App::~App() {
  this->borderPos = 0;
  this->horizontal = false;
  this->showCode = false;
  this->editMode = false;
  this->editStrMode = false;
  this->asciiMode = false;
}

void App::Init(WINDOW* win) {
  this->win = win;
  this->codeView = new CodeView();
  this->termView = new TerminalView();
  this->lineView = new LineView();
}

void App::Draw() {
  getmaxyx(stdscr, this->rows, this->cols);

  if (this->cols < 3 || this->rows < 3) {
    clear();
    return;
  }

  if (this->borderPos > 1) this->borderPos = 1;

  if (this->horizontal) {
    if (this->showCode) {
      int line = (this->rows - 1) * this->borderPos;
      if (line <= 0) line = 1;

      this->codeView->bounds->X(0);
      this->codeView->bounds->Y(0);
      this->codeView->bounds->Height(line);
      this->codeView->bounds->Width(this->cols);

      this->termView->bounds->X(0);
      this->termView->bounds->Y(line + 1);
      this->termView->bounds->Height(this->rows - 1 - line);
      this->termView->bounds->Width(this->cols);

      this->lineView->bounds->X(0);
      this->lineView->bounds->Y(line);
      this->lineView->bounds->Height(1);
      this->lineView->bounds->Width(this->cols);

    } else {
      this->codeView->bounds->X(0);
      this->codeView->bounds->Y(0);
      this->codeView->bounds->Height(0);
      this->codeView->bounds->Width(this->cols);

      this->termView->bounds->X(0);
      this->termView->bounds->Y(1);
      this->termView->bounds->Height(this->rows - 1);
      this->termView->bounds->Width(this->cols);

      this->lineView->bounds->X(0);
      this->lineView->bounds->Y(0);
      this->lineView->bounds->Height(1);
      this->lineView->bounds->Width(this->cols);
    }
  } else {
    if (this->showCode) {
      int line = (this->cols - 1) * this->borderPos;
      if (line <= 0) line = 1;

      this->codeView->bounds->X(0);
      this->codeView->bounds->Y(0);
      this->codeView->bounds->Height(this->rows);
      this->codeView->bounds->Width(line);

      this->termView->bounds->X(line + 1);
      this->termView->bounds->Y(0);
      this->termView->bounds->Height(this->rows);
      this->termView->bounds->Width(this->cols - 1 - line);

      this->lineView->bounds->X(line);
      this->lineView->bounds->Y(0);
      this->lineView->bounds->Height(this->rows);
      this->lineView->bounds->Width(1);

    } else {
      this->codeView->bounds->X(0);
      this->codeView->bounds->Y(0);
      this->codeView->bounds->Height(this->rows);
      this->codeView->bounds->Width(0);

      this->termView->bounds->X(1);
      this->termView->bounds->Y(0);
      this->termView->bounds->Height(this->rows);
      this->termView->bounds->Width(this->cols - 1);

      this->lineView->bounds->X(0);
      this->lineView->bounds->Y(0);
      this->lineView->bounds->Height(this->rows);
      this->lineView->bounds->Width(1);
    }
  }

  if (this->showCode) {
    this->codeView->Update();
  }
  this->lineView->Update();
  this->termView->Update();

  if (this->showCode) {
    this->codeView->Draw();
  }
  this->lineView->Draw();
  this->termView->Draw();

  update_panels();
  doupdate();
}

#endif
