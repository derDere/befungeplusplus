#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include <vector>
#include <ncursesw/panel.h>
#include <ncursesw/ncurses.h>

#include "colors.hpp"

#define DIALOG_BUTTONS_OK_ONLY 1
#define DIALOG_BUTTONS_OK_CANCEL 2
#define DIALOG_BUTTONS_YES_NO 3
#define DIALOG_BUTTONS_YES_NO_CANCEL 4

using namespace std;

struct DialogButton {
  int id;
  string text;
  char shortcut;
};

#define DIALOG_RESULT_OK 1
#define DIALOG_RESULT_CANCEL 2
#define DIALOG_RESULT_YES 3
#define DIALOG_RESULT_NO 4

#define DIALOG_OK_BTN { DIALOG_RESULT_OK, "OK", 'o' }
#define DIALOG_CANCEL_BTN { DIALOG_RESULT_CANCEL, "Cancel", 'c' }
#define DIALOG_YES_BTN { DIALOG_RESULT_YES, "Yes", 'y' }
#define DIALOG_NO_BTN { DIALOG_RESULT_NO, "No", 'n' }

struct DialogResult {
  int id;
  string value;
};

class Dialog {

  private:
    WINDOW* win;
    PANEL* panel;
    int cols, rows;
    bool run;

    string title;
    string message;
    string value;
    int buttonType;


  public:
    Dialog();
    ~Dialog();

    Dialog* Title(string);
    Dialog* Message(string);
    Dialog* Buttons(int);
    Dialog* Value(string);

    DialogResult Show();

    static Dialog* MessageBox();
    static Dialog* InputBox();
};

#endif
