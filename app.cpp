#ifndef APP_CPP
#define APP_CPP

#include "app.hpp"

using namespace std;
using namespace BefungePlusPlus;

App::App() {
  this->borderPos = 0.5;
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
}

void App::Draw() {
  getmaxyx(stdscr, this->rows, this->cols);
  int line = this->rows * this->borderPos;

  string LINE;
  if (this->asciiMode) {
    LINE = "-";
  } else {
    LINE = "─";
  }

  clear();

  mvaddstr(line + 1, 0, LINE.c_str());
  for(int i = 1; i < cols; i++) {
    addstr(LINE.c_str());
  }
}

#endif
