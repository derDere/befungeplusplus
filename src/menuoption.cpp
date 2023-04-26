#ifndef MENUOPTION_CPP
#define MENUOPTION_CPP

#include "menuoption.hpp"

using namespace std;

MenuOption::MenuOption(string display, int shortcut) {
  this->display = display;
  this->shortcut = shortcut;
}

MenuOption::~MenuOption() {
  this->display = "";
  this->shortcut = '\0';
}

string MenuOption::Display() {
  return this->display;
}

int MenuOption::Shortcut() {
  return this->shortcut;
}

bool MenuOption::IsShortcut(int key) {
  return this->shortcut == key;
}

#endif
