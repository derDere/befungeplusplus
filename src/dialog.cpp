#ifndef DIAGLOG_CPP
#define DIAGLOG_CPP

#include "dialog.hpp"

using namespace std;

Dialog::Dialog() {
  this->win = nullptr;
  this->panel = nullptr;
  this->cols = 0;
  this->rows = 0;
  this->title = "Unkown";
  this->message = "Message not set";
  this->value = "";
  this->buttonType = DIALOG_BUTTONS_OK_ONLY;
  this->colors = DIALOG_DEFAULT_PAIR;
  this->inputActive = false;
}

Dialog::~Dialog() {
  if (this->panel != nullptr) {
    del_panel(this->panel);
  }
  if (this->win != nullptr) {
    delwin(this->win);
  }

  this->win = nullptr;
  this->panel = nullptr;
  this->cols = 0;
  this->rows = 0;
  this->title = "";
  this->message = "";
  this->value = "";
  this->buttonType = 0;
  this->colors = 0;
  this->inputActive = false;
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

Dialog* Dialog::ColorDefault() {
  this->colors = DIALOG_DEFAULT_PAIR;
  return this;
}

Dialog* Dialog::ColorInfo() {
  this->colors = DIALOG_INFO_PAIR;
  return this;
}

Dialog* Dialog::ColorWarning() {
  this->colors = DIALOG_WARNING_PAIR;
  return this;
}

Dialog* Dialog::ColorError() {
  this->colors = DIALOG_ERROR_PAIR;
  return this;
}

Dialog* Dialog::Input() {
  this->inputActive = true;
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
  // Create window
  this->win = newwin(1, 1, 0, 0);
  this->panel = new_panel(this->win);
  top_panel(this->panel);

  int selectedIndex = 0;
  if (this->inputActive) {
    selectedIndex = -1;
  }
  bool run = true;
  DialogResult result = { DIALOG_RESULT_CANCEL, "" };
  while (run) {
    // Calculate window size
    int cols, rows;
    getmaxyx(stdscr, rows, cols);
    int winWidth = cols;
    if (winWidth < DIALOG_MIN_WIN_WIDTH) winWidth = DIALOG_MIN_WIN_WIDTH;
    if (winWidth > DIALOG_MAX_WIN_WIDTH) winWidth = DIALOG_MAX_WIN_WIDTH;

    int lineLength = winWidth - 4;
    vector<string>* lines = WordWrap(this->message, lineLength);
    int maxLineLength = DIALOG_MIN_WIN_WIDTH;
    for (int i = 0; i < lines->size(); i++) {
      if (lines->at(i).length() > maxLineLength) {
        maxLineLength = lines->at(i).length();
      }
    }

    if (winWidth > maxLineLength + 4) {
      winWidth = maxLineLength + 4;
    }
    int winHeight = 6 + lines->size();
    if (this->inputActive) {
      winHeight += 2;
    }

    // Calculate window position
    int top = (rows - winHeight) / 2;
    int left = (cols - winWidth) / 2;

    // Resize window
    wresize(this->win, winHeight, winWidth);
    mvwin(this->win, top, left);
    move_panel(this->panel, top, left);
    wclear(this->win);

    // Draw window
    wbkgd(this->win, COLOR_PAIR(this->colors));
    box(this->win, 0, 0);
    mvwaddstr(this->win, 2, 0, "├");
    for (int i = 1; i < winWidth - 1; i++) {
      mvwaddstr(this->win, 2, i, "─");
    }
    mvwaddstr(this->win, 2, winWidth - 1, "┤");

    // Draw title
    string title = this->title;
    if (title.length() > winWidth - 4) {
      title = title.substr(0, winWidth - 7) + "...";
    }
    mvwaddstr(this->win, 1, (winWidth - title.length()) / 2, title.c_str());

    // Draw message
    for (int i = 0; i < lines->size(); i++) {
      mvwaddstr(this->win, 3 + i, 2, lines->at(i).c_str());
    }

    // Draw buttons
    int buttonRow = 3 + lines->size() + 1;
    if (this->inputActive) {
      buttonRow += 2;
    }
    string buttonLine = "";
    int buttonIndex = 0;
    vector<DialogButton> buttons = {};
    vector<DialogButton> allButtons = {
      DIALOG_OK_BTN,
      DIALOG_YES_BTN,
      DIALOG_NO_BTN,
      DIALOG_CANCEL_BTN
    };

    {
      for (vector<DialogButton>::iterator btn = allButtons.begin(); btn != allButtons.end(); btn++) {
        if ((this->buttonType & btn->id) == btn->id) {
          btn->index = buttonIndex;
          if (btn->space) {
            btn->index += 1;
            buttonLine += " ";
          }
          buttonLine += ((buttons.size() == selectedIndex) ? "[" : " ");
          buttonLine += btn->shortcut;
          buttonLine += btn->text;
          buttonLine += ((buttons.size() == selectedIndex) ? "]" : " ");
          buttonIndex = buttonLine.length();
          buttons.push_back(*btn);
        }
      }
    }

    int buttonLeft = (winWidth - buttonLine.length()) / 2;
    mvwaddstr(this->win, buttonRow, buttonLeft, buttonLine.c_str());
    for (vector<DialogButton>::iterator btn = buttons.begin(); btn != buttons.end(); btn++) {
      wattron(this->win, A_REVERSE);
      mvwaddch(this->win, buttonRow, buttonLeft + btn->index + 1, btn->shortcut);
      wattroff(this->win, A_REVERSE);
    }

    // Draw input
    if (this->inputActive) {
      string inputLine = this->value;
      if (inputLine.length() > winWidth - 6) {
        inputLine = inputLine.substr(inputLine.length() - (winWidth - 6));
      }
      if (selectedIndex == -1) mvwaddch(this->win, buttonRow - 2, 2, '[');
      wattron(this->win, A_REVERSE);
      mvwaddstr(this->win, buttonRow - 2, 3, inputLine.c_str());
      for (int x = 3 + inputLine.length(); x < winWidth - 3; x++) {
        mvwaddch(this->win, buttonRow - 2, x, ' ');
      }
      wattroff(this->win, A_REVERSE);
      if (selectedIndex == -1) mvwaddch(this->win, buttonRow - 2, winWidth - 3, ']');
    }

    // Update Panels
    show_panel(this->panel);
    update_panels();
    doupdate();

    // Handle input
    int input = wgetch(stdscr);
    if (input == KEY_MOUSE) {
      MEVENT event;
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          int x = event.x - left;
          int y = event.y - top;
          if (y == buttonRow) {
            for (vector<DialogButton>::iterator btn = buttons.begin(); btn != buttons.end(); btn++) {
              if (x >= (buttonLeft + btn->index) && x < (buttonLeft + btn->index + btn->text.length() + 3)) {
                result = { btn->id, this->value };
                run = false;
              }
            }
          }
        }
      }

    } else {
      if (input == '\t') {
        selectedIndex++;
        if (selectedIndex >= buttons.size()) {
          if (this->inputActive) {
            selectedIndex = -1;
          } else {
            selectedIndex = 0;
          }
        }
      } else if (input == KEY_SHIFT_TAB) {
        selectedIndex--;
        if (
          (selectedIndex <= -1 && !this->inputActive) ||
          (selectedIndex <= -2 && this->inputActive)
        ) {
          selectedIndex = buttons.size() - 1;
        }
      } else if (input == KEY_UP) {
        if (this->inputActive) {
          selectedIndex = -1;
        }
      } else if (input == KEY_DOWN) {
        if (this->inputActive) {
          selectedIndex = 0;
        }
      } else if (input == KEY_LEFT) {
        if (selectedIndex > 0) {
          selectedIndex--;
        }
      } else if (input == KEY_RIGHT) {
        if (selectedIndex < buttons.size() - 1) {
          selectedIndex++;
        }
      } else {
        if (selectedIndex == -1) {
          if (input == '\n') {
            selectedIndex = 0;
          } else if (input == KEY_BACKSPACE) {
            if (this->value.length() > 0) {
              this->value = this->value.substr(0, this->value.length() - 1);
            }
          } else if (input >= 32 && input <= 126) {
            this->value += input;
          }

        } else {
          if (input == '\n') {
            DialogButton btn = buttons.at(selectedIndex);
            result = { btn.id, this->value };
            run = false;
          } else {
            int i = 0;
            for (vector<DialogButton>::iterator btn = buttons.begin(); btn != buttons.end(); btn++, i++) {
              if (input == btn->shortcut) {
                selectedIndex = i;
              }
            }
          }
        }
      }
    }
  }

  //delete this;
  return result;
}

#endif
