#ifndef LINEVIEW_CPP
#define LINEVIEW_CPP

#include "lineview.hpp"

using namespace std;

LineView::LineView() {
  this->code = "Line -----------------------------------";
}

LineView::~LineView() {
  this->code = "";
}

void LineView::Draw() {
  wattron(this->win, A_REVERSE);
  int len = this->bounds->Height();
  if (len < this->bounds->Width()) {
    len = this->bounds->Width();
  }
  mvwaddstr(this->win, 0, 0, " Line ");
  for(int i = 6; i < len; i++) {
    waddstr(this->win, " ");
  }
  wattroff(this->win, A_REVERSE);
}

void LineView::Update() {
  this->Reposition();
}

#endif
