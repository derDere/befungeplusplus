#ifndef TERMINALVIEW_CPP
#define TERMINALVIEW_CPP

#include <string>
#include "terminalview.hpp"

using namespace std;

TerminalView::TerminalView() {
  this->code = "Terminal";
}

TerminalView::~TerminalView() {
  this->code = "";
}

void TerminalView::Draw() {
  mvwaddstr(this->win, 0, 0, this->code.c_str());
}

void TerminalView::Update() {
  this->Reposition();
}

#endif
