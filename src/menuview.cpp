#ifndef MENUVIEW_CPP
#define MENUVIEW_CPP

#include "menuview.hpp"

using namespace std;

MenuView::MenuView() {
  this->selected = 0;

  this->options = new vector<MenuOption*>();
  this->AddOption("New     ", 'n');
  this->AddOption("────────", '\0');
  this->AddOption("Save    ", 's');
  this->AddOption("Save As ", 'S');
  this->AddOption("────────", '\0');
  this->AddOption("Open    ", 'o');
  this->AddOption("────────", '\0');
  this->AddOption("Quit    ", 'q');

  this->bounds->X(0);
  this->bounds->Y(1);
  this->bounds->Width(14);
  this->bounds->Height(this->options->size() + 2);

  this->open = false;
}

MenuView::~MenuView() {
  this->options->clear();
  delete this->options;
  this->selected = 0;
}

void MenuView::AddOption(string display, int shortcut) {
  this->options->push_back(new MenuOption(display, shortcut));
}

void MenuView::RemoveOption(int index) {
  this->options->erase(this->options->begin() + index);
}

void MenuView::ClearOptions() {
  this->options->clear();
}

void MenuView::Inject(int key) {
  if (key == KEY_DOWN) {
    do {
      this->selected++;
      if (this->selected >= this->options->size()) {
        this->selected = 0;
      }
    } while (this->options->at(this->selected)->Shortcut() == '\0');

  } else if (key == KEY_UP) {
    do {
      this->selected--;
      if (this->selected < 0) {
        this->selected = this->options->size() - 1;
      }
    } while (this->options->at(this->selected)->Shortcut() == '\0');

  } else if (key == KEY_ENTER || key == '\n' || key == '\r') {

  } else {
    for (int i = 0; i < this->options->size(); i++) {
      if (this->options->at(i)->IsShortcut(key)) {
        this->selected = i;
        break;
      }
    }
  }
}

void MenuView::Open() {
  this->open = true;
}

void MenuView::Close() {
  this->open = false;
}

bool MenuView::IsOpen() {
  return this->open;
}

void MenuView::Draw() {
  if (!this->open) {
    this->Hide();
    return;
  }
  this->Show();

  wbkgd(this->win, COLOR_PAIR(MENU_COLOR_PAIR));
  box(this->win, 0, 0);

  for (int i = 0; i < this->options->size(); i++) {
    MenuOption* option = this->options->at(i);
    if (option->Shortcut() != '\0' && i == this->selected) {
      wattron(this->win, COLOR_PAIR(MENU_SELECTED_PAIR));
      mvwaddch(this->win, i + 1, 1, '[');
      waddch(this->win, option->Shortcut());
      waddstr(this->win, "] ");
      waddstr(this->win, option->Display().substr(0, this->bounds->Width() - 6).c_str());
      wattroff(this->win, COLOR_PAIR(MENU_SELECTED_PAIR));
    } else {
      if (option->Shortcut() == '\0') {
        mvwaddstr(this->win, i + 1, 0, "├");
        for (int j = 0; j < this->bounds->Width() - 2; j++) {
          mvwaddstr(this->win, i + 1, j + 1, "─");
        }
        mvwaddstr(this->win, i + 1, this->bounds->Width() - 1, "┤");
      } else {
        mvwaddch(this->win, i + 1, 1, '[');
        waddch(this->win, option->Shortcut());
        waddstr(this->win, "] ");
        waddstr(this->win, option->Display().substr(0, this->bounds->Width() - 6).c_str());
      }
    }
  }
}

void MenuView::Update() {
  this->Reposition();
}

#endif
