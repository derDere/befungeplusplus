#ifndef STACKVIEW_CPP
#define STACKVIEW_CPP

#include <string>
#include "stackview.hpp"

using namespace std;

StackView::StackView() {
  this->code = "Stack";
}

StackView::~StackView() {
  this->code = "";
}

void StackView::Draw() {
  wbkgd(this->win, COLOR_PAIR(STACK_COLOR_PAIR));
  //wclear(this->win);
  mvwaddstr(this->win, 0, 0, this->code.c_str());
}

void StackView::Update() {
  this->Reposition();
}

#endif
