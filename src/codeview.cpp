#ifndef CODEVIEW_CPP
#define CODEVIEW_CPP

#include <string>
#include "codeview.hpp"

using namespace std;

CodeView::CodeView(Matrix* matrix, Editor* editor, Runner* runner) {
  this->matrix = matrix;
  this->editor = editor;
  this->runner = runner;
}

CodeView::~CodeView() {}

void CodeView::Draw() {
  wbkgd(this->win, COLOR_PAIR(CODE_COLOR_PAIR));
  wclear(this->win);
  wmove(this->win, 0, 0);
  char c;
  bool changed;
  for (int y = 0; y < this->bounds->Height(); y++) {
    for (int x = 0; x < this->bounds->Width(); x++) {
      c = this->matrix->Get({x, y});
      if (this->matrix->Changed({x, y})) {
        wattron(this->win, COLOR_PAIR(CODE_CHANGE_PAIR));
        waddch(this->win, c);
        wattroff(this->win, COLOR_PAIR(CODE_CHANGE_PAIR));
      } else {
        if (this->runner->is(x, y)) {
          wattron(this->win, COLOR_PAIR(CODE_RUNNER_PAIR));
          waddch(this->win, c);
          wattroff(this->win, COLOR_PAIR(CODE_RUNNER_PAIR));

        } else if (this->editor->position->is(x, y)) {
          wattron(this->win, COLOR_PAIR(CODE_CURSOR_PAIR));
          waddch(this->win, c);
          wattroff(this->win, COLOR_PAIR(CODE_CURSOR_PAIR));

        } else if (
          (this->editor->position->X() == x) ||
          (this->editor->position->Y() == y)
        ) {
          wattron(this->win, COLOR_PAIR(CODE_CROSS_PAIR));
          waddch(this->win, c);
          wattroff(this->win, COLOR_PAIR(CODE_CROSS_PAIR));

        } else {
          switch (c)
          {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '!':
            case '`':
            case '"':
            case ':':
            case '\\':
            case '$':
            case '.':
            case ',':
            case '#':
            case '&':
            case '~':
                wattron(this->win, A_BOLD);
                wattron(this->win, COLOR_PAIR(CODE_CMD_PAIR));
                waddch(this->win, c);
                wattroff(this->win, COLOR_PAIR(CODE_CMD_PAIR));
                wattroff(this->win, A_BOLD);
              break;

            case '|':
            case '_':
            case '?':
                wattron(this->win, COLOR_PAIR(CODE_PATH_PAIR));
                waddch(this->win, c);
                wattroff(this->win, COLOR_PAIR(CODE_PATH_PAIR));
              break;

            case '^':
                wattron(this->win, COLOR_PAIR(CODE_PATH_PAIR));
                waddstr(this->win, "▲");
                wattroff(this->win, COLOR_PAIR(CODE_PATH_PAIR));
              break;
            case '<':
                wattron(this->win, COLOR_PAIR(CODE_PATH_PAIR));
                waddstr(this->win, "◄");
                wattroff(this->win, COLOR_PAIR(CODE_PATH_PAIR));
              break;
            case '>':
                wattron(this->win, COLOR_PAIR(CODE_PATH_PAIR));
                waddstr(this->win, "►");
                wattroff(this->win, COLOR_PAIR(CODE_PATH_PAIR));
              break;
            case 'v':
                wattron(this->win, COLOR_PAIR(CODE_PATH_PAIR));
                waddstr(this->win, "▼");
                wattroff(this->win, COLOR_PAIR(CODE_PATH_PAIR));
              break;

            case '@':
            case ';':
                wattron(this->win, A_BOLD);
                wattron(this->win, COLOR_PAIR(CODE_SPECIAL_PAIR));
                waddch(this->win, c);
                wattroff(this->win, COLOR_PAIR(CODE_SPECIAL_PAIR));
                wattroff(this->win, A_BOLD);
              break;

            default:
                waddch(this->win, c);
              break;
          }
        }
      }
    }
  }
}

void CodeView::Update() {
  this->Reposition();
}

#endif
