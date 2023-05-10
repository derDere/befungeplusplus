#ifndef DIAGLOG_CPP
#define DIAGLOG_CPP

#include "dialog.hpp"

#include <iostream>

using namespace std;

Dialog::Dialog() {
  this->win = nullptr;
  this->panel = nullptr;
  this->cols = 0;
  this->rows = 0;
  this->run = false;
  this->title = "Unkown";
  this->message = "Message not set";
  this->value = "";
  this->buttonType = DIALOG_BUTTONS_OK_ONLY;
}

Dialog::~Dialog() {
  if (this->win != nullptr) {
    delwin(this->win);
  }

  if (this->panel != nullptr) {
    del_panel(this->panel);
  }

  this->win = nullptr;
  this->panel = nullptr;
  this->cols = 0;
  this->rows = 0;
  this->run = false;
  this->title = "";
  this->message = "";
  this->value = "";
  this->buttonType = 0;
}

Dialog* Dialog::Title(string title) {
  this->title = title;
  return this;
}

Dialog* Dialog::Message(string message) {
  this->message = message;
  return this;
}

Dialog* Dialog::Buttons(int buttonType) {
  this->buttonType = buttonType;
  return this;
}

Dialog* Dialog::Value(string value) {
  this->value = value;
  return this;
}

/**
 * @brief Takes a multiline string and splits it into a vector of strings with a maximum length of lineMaxLength.
 *        Lines will be sepearted at the last space or with every newline character.
 */
vector<string>* WordWrap(string message, int lineMaxLength) {
  vector<string>* lines = new vector<string>();
  string line = "";
  int lineLength = 0;

  while (message.length() > 0) {
    if (message[0] == '\n') {
      lines->push_back(line);
      line = "";
      lineLength = 0;
      message = message.substr(1);
      continue;
    }

    if (lineLength >= lineMaxLength) {
      int lastSpace = line.find_last_of(' ');
      if (lastSpace == string::npos) {
        lines->push_back(line);
        line = "";
        lineLength = 0;
        continue;
      }

      lines->push_back(line.substr(0, lastSpace));
      line = line.substr(lastSpace + 1);
      lineLength = line.length();
      continue;
    }

    line += message[0];
    lineLength++;
    message = message.substr(1);
  }

  if (line.length() > 0) {
    lines->push_back(line);
  }

  return lines;
}

DialogResult Dialog::Show() {
  // Calculate window size
  int cols, rows;
  getmaxyx(stdscr, rows, cols);
  int winWidth = cols;
  if (winWidth < 26) winWidth = 26;
  if (winWidth > 60) winWidth = 60;

  int lineLength = winWidth - 4;
  vector<string>* lines = WordWrap(this->message, lineLength);

  int winHeight = 6 + lines->size();

  // Calculate window position
  int top = (rows - winHeight) / 2;
  int left = (cols - winWidth) / 2;

  // Create window
  this->win = newwin(winHeight, winWidth, top, left);
  this->panel = new_panel(this->win);
  show_panel(this->panel);

  // Draw window
  wbkgd(this->win, COLOR_PAIR(COLOR_DIALOG));
  box(this->win, 0, 0);


  this->run = true;

  return { DIALOG_RESULT_OK, "" };
}

#endif
