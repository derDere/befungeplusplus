#ifndef CODEVIEW_CPP
#define CODEVIEW_CPP

#include <string>
#include "codeview.hpp"

using namespace std;

CodeView::CodeView() {
  this->code = "Code";
}

CodeView::~CodeView() {
  this->code = "";
}

void CodeView::Draw() {
  mvwaddstr(this->win, 0, 0, this->code.c_str());
}

void CodeView::Update() {
  this->Reposition();
}

#endif
