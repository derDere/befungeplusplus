#ifndef CODEVIEW_CPP
#define CODEVIEW_CPP

#include <string>
#include "codeview.hpp"

using namespace std;

CodeView::CodeView(Matrix* matrix, Editor* editor, Runner* runner) {
  this->matrix = matrix;
  this->editor = editor;
  this->runner = runner;
  this->viewPoint = new Point(-4, -2);
  this->showCross = false;
}

CodeView::~CodeView() {
  this->showCross = false;
  delete this->viewPoint;
}

int CodeView::viewX() {
  return this->viewPoint->X();
}

int CodeView::viewY() {
  return this->viewPoint->Y();
}

void CodeView::Update() {
  this->Reposition();

  // Calculate margins
  int xm = (this->bounds->Width() - 1) / 2;
  int ym = (this->bounds->Height() - 1) / 2;
  if (xm > 4) xm = 4;
  if (ym > 2) ym = 2;

  // Move ViewPoint
  if (this->viewPoint->X() < (this->editor->position->X() - this->bounds->Width() + xm + 1)) this->viewPoint->X(this->editor->position->X() - this->bounds->Width() + xm + 1);
  if (this->viewPoint->Y() < (this->editor->position->Y() - this->bounds->Height() + ym + 1)) this->viewPoint->Y(this->editor->position->Y() - this->bounds->Height() + ym + 1);
  if (this->viewPoint->X() > (this->editor->position->X() - xm)) this->viewPoint->X(this->editor->position->X() - xm);
  if (this->viewPoint->Y() > (this->editor->position->Y() - ym)) this->viewPoint->Y(this->editor->position->Y() - ym);
}

void CodeView::Draw() {
  //wbkgd(this->win, COLOR_PAIR(CODE_COLOR_PAIR));
  //wclear(this->win);
  wmove(this->win, 0, 0);
  char c;
  bool changed;
  int xo = this->viewPoint->X();
  int yo = this->viewPoint->Y();
  for (int yi = 0; yi < this->bounds->Height(); yi++) {
    for (int xi = 0; xi < this->bounds->Width(); xi++) {
      int x = xi + xo;
      int y = yi + yo;
      c = this->matrix->Get({x, y});
      if (this->matrix->Changed({x, y})) {
        wattron(this->win, COLOR_PAIR(CODE_CHANGE_PAIR));
        waddch(this->win, c);
        wattroff(this->win, COLOR_PAIR(CODE_CHANGE_PAIR));

      } else {
        if (this->editor->position->Is(x, y)) {
          wattron(this->win, A_BLINK);
          wattron(this->win, COLOR_PAIR(CODE_CURSOR_PAIR));
          waddch(this->win, c);
          wattroff(this->win, COLOR_PAIR(CODE_CURSOR_PAIR));
          wattroff(this->win, A_BLINK);

        } else if (this->runner->Is(x, y)) {
          wattron(this->win, COLOR_PAIR(CODE_RUNNER_PAIR));
          waddch(this->win, c);
          wattroff(this->win, COLOR_PAIR(CODE_RUNNER_PAIR));

        } else if (
          (
            (this->editor->position->X() == x) ||
            (this->editor->position->Y() == y)
          ) &&
          this->showCross
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

#endif
