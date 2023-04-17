#ifndef	VIEW_CPP
#define VIEW_CPP

#include "view.hpp"
#include <iostream>

using namespace std;

View::View() {
  this->bounds = new Rect(3, 3, 50, 50);

  this->win = newwin(
    this->bounds->Height(),
    this->bounds->Width(),
    this->bounds->Y(),
    this->bounds->X()
  );

  cout << this->bounds->Height() << endl;
  cout << this->bounds->Width() << endl;
  cout << this->bounds->Y() << endl;
  cout << this->bounds->X() << endl;

  this->pan = new_panel(this->win);
  show_panel(this->pan);
}

View::~View() {
  del_panel(this->pan);
  delwin(this->win);
  delete this->bounds;
}

void View::Reposition() {
  wresize(this->win, this->bounds->Height(), this->bounds->Width());
  mvwin(this->win, this->bounds->Y(), this->bounds->X());
  move_panel(this->pan, this->bounds->Y(), this->bounds->X());
}

#endif
