#ifndef HELPVIEW_CPP
#define HELPVIEW_CPP

#include "helpview.hpp"

using namespace std;

HelpView::HelpView() {
  this->code = "HelpView";
  this->visible = false;
  this->bounds->Width(20);
  this->bounds->Height(10);
}

HelpView::~HelpView() {
  this->code = "";
  this->visible = false;
}

void HelpView::Open() {
  this->visible = true;
}

void HelpView::Close() {
  this->visible = false;
}

bool HelpView::IsVisible() {
  return this->visible;
}

void HelpView::Update() {
  this->Reposition();
}

void HelpView::Draw() {
  if (!this->visible) {
    this->Hide();
    return;
  }
  this->Show();

  wbkgd(this->win, COLOR_PAIR(HELP_COLOR_PAIR));
  wattron(this->win, COLOR_PAIR(HELP_COLOR_PAIR));
  box(this->win, 0, 0);
  mvwaddstr(this->win, 1, 1, this->code.c_str());
  wattroff(this->win, COLOR_PAIR(HELP_COLOR_PAIR));
}

#endif
