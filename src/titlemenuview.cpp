#ifndef TITLEMENUVIEW_CPP
#define TITLEMENUVIEW_CPP

#include <string>
#include <vector>
#include "titlemenuview.hpp"

using namespace std;

TitleMenuView::TitleMenuView() {
  this->title = "Title";
}

TitleMenuView::~TitleMenuView() {
  this->title = "";
}

void TitleMenuView::Draw() {
  wbkgd(this->win, COLOR_PAIR(TITLE_COLOR_PAIR));

  int x = 0;
  vector<string> info = {
    "^a", "Menu",
  //  "^s", "Save",
  //  "^o", "Open",
  //  "^q", "Quit",
    "^h", "Help",
  //  "^c", "Copy",
  //  "^v", "Paste",
  //  "^x", "Cut",
    "F5", "Run",
    "F11", "Step",
    "F9", "Stop"
  };

  wmove(this->win, 0, 0);
  wattron(this->win, A_REVERSE);
  for(vector<string>::iterator it = info.begin(); it != info.end(); it+=2) {
    string s1 = *it;
    string s2 = *(it+1);

    wattroff(this->win, A_REVERSE);
    waddstr(this->win, s1.c_str());
    wattron(this->win, A_REVERSE);
    x += s1.length();

    waddstr(this->win, s2.c_str());
    waddstr(this->win, " ");
    x += s2.length() + 1;
  }
  wattroff(this->win, A_REVERSE);

  int half = (this->bounds->Width() - this->title.length() - x) / 2;
  for(int i = 0; i < half; i++) {
    waddstr(this->win, " ");
  }
  waddstr(this->win, this->title.c_str());
  for(int i = 0; i < half; i++) {
    waddstr(this->win, " ");
  }
}

void TitleMenuView::Update() {
  this->Reposition();
}

#endif
