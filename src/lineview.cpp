#ifndef LINEVIEW_CPP
#define LINEVIEW_CPP

#include "lineview.hpp"

using namespace std;

LineView::LineView() {
  this->code = "Line ";
}

LineView::~LineView() {
  this->code = "";
}

void LineView::Draw() {
  wbkgd(this->win, COLOR_PAIR(LINE_COLOR_PAIR));
  wclear(this->win);
  mvwaddstr(this->win, 0, 0, this->code.c_str());
}

void LineView::Update() {
  this->Reposition();
}

#endif
