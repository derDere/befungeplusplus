#ifndef TITLEMENUVIEW_CPP
#define TITLEMENUVIEW_CPP

#include <string>
#include "titlemenuview.hpp"

using namespace std;

TitleMenuView::TitleMenuView() {
  this->code = "Title";
}

TitleMenuView::~TitleMenuView() {
  this->code = "";
}

void TitleMenuView::Draw() {
  wbkgd(this->win, COLOR_PAIR(TITLE_COLOR_PAIR));
  wclear(this->win);
  mvwaddstr(this->win, 0, 0, this->code.c_str());
}

void TitleMenuView::Update() {
  this->Reposition();
}

#endif
