#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include <vector>
#include <ncursesw/panel.h>
#include <ncursesw/ncurses.h>

#include "colors.hpp"

#define DIALOG_MIN_WIN_WIDTH 26
#define DIALOG_MAX_WIN_WIDTH 160

using namespace std;

struct DialogButton {
  int id;
  string text;
  char shortcut;
  int index;
  bool space;
};

#define DIALOG_RESULT_OK 1
#define DIALOG_RESULT_CANCEL 2
#define DIALOG_RESULT_YES 4
#define DIALOG_RESULT_NO 8

#define DIALOG_BUTTONS_OK_ONLY DIALOG_RESULT_OK
#define DIALOG_BUTTONS_OK_CANCEL DIALOG_RESULT_OK | DIALOG_RESULT_CANCEL
#define DIALOG_BUTTONS_YES_NO DIALOG_RESULT_YES | DIALOG_RESULT_NO
#define DIALOG_BUTTONS_YES_NO_CANCEL DIALOG_RESULT_YES | DIALOG_RESULT_NO | DIALOG_RESULT_CANCEL

#define DIALOG_OK_BTN { DIALOG_RESULT_OK, "OK", 'o', -1, false }
#define DIALOG_CANCEL_BTN { DIALOG_RESULT_CANCEL, "Cancel", 'c', -1, true }
#define DIALOG_YES_BTN { DIALOG_RESULT_YES, "Yes", 'y', -1, false }
#define DIALOG_NO_BTN { DIALOG_RESULT_NO, "No", 'n', -1, true }

struct DialogResult {
  int id;
  string value;
};

class Dialog {

  private:
    WINDOW* win;
    PANEL* panel;
    int cols, rows;

    string title;
    string message;
    string value;
    int colors;
    int buttonType;


  public:
    Dialog();
    ~Dialog();

    Dialog* Title(string);
    Dialog* Message(string);
    Dialog* Buttons(int);
    Dialog* Value(string);
    Dialog* ColorDefault();
    Dialog* ColorInfo();
    Dialog* ColorWarning();
    Dialog* ColorError();

    DialogResult Show();

    static Dialog* MessageBox();
    static Dialog* InputBox();
};

#endif
