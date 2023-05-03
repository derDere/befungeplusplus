#ifndef TITLEMENUVIEW_CPP
#define TITLEMENUVIEW_CPP

#include <string>
#include <vector>
#include <iostream>
#include "titlemenuview.hpp"

using namespace std;

TitleMenuView::TitleMenuView(MenuView* menuView) {
  this->menuView = menuView;
  this->title = "Title";
  this->quitRequested = false;
}

TitleMenuView::~TitleMenuView() {
  this->menuView = NULL;
  this->title = "";
  this->quitRequested = false;
}

void TitleMenuView::SetTitle(string title) {
  this->title = title;
}

bool TitleMenuView::IsQuitRequested() {
  bool q = this->quitRequested;
  this->quitRequested = false;
  return q;
}

void TitleMenuView::MouseInject(MEVENT event) {
  if(event.bstate & BUTTON1_CLICKED) {
    if (event.y == 0) {
      if (event.x <= 8 && !this->menuView->IsOpen()) {
        this->menuView->Open();

      } else if (event.x <= 15) {
        // TODO: Toggle Help

      } else if (event.x <= 21) {
        // TODO: Start Run

      } else if (event.x <= 29) {
        // TODO: Do Step

      } else if (event.x <= 36) {
        // TODO: Stop Run

      } else if (event.x >= (this->bounds->Width() - 6)) {
        this->quitRequested = true;
      }
    }
  }
}

void TitleMenuView::Draw() {
  wbkgd(this->win, COLOR_PAIR(TITLE_COLOR_PAIR));

  int x = 6;
  vector<string> info = {
    "^spc", "Menu",
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
  int half2 = (this->bounds->Width() - this->title.length() - x) - half;
  for(int i = 0; i < half; i++) {
    waddstr(this->win, " ");
  }
  waddstr(this->win, this->title.c_str());
  for(int i = 0; i < half2; i++) {
    waddstr(this->win, " ");
  }

  wattron(this->win, A_REVERSE);
  waddstr(this->win, "^q");
  wattroff(this->win, A_REVERSE);

  waddstr(this->win, "Quit");
}

void TitleMenuView::Update() {
  this->Reposition();
}

#endif
