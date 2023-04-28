#ifndef APP_CPP
#define APP_CPP

#include "app.hpp"
#include "advkeys.hpp"

using namespace std;
using namespace BefungePlusPlus;

App::App() {
  this->matrix = new Matrix();
  this->runner = new Runner();
  this->editor = new Editor(this->matrix);

  //for(int x = 0; x < 160; x++) {
  //  for(int y = 0; y < 80; y++) {
  //    this->matrix->Set({x,y}, '.');
  //  }
  //}
  //
  //this->matrix->Set({0,0}, '@');
  //this->matrix->Set({1,1}, '^');
  //this->matrix->Set({2,2}, '>');
  //this->matrix->Set({3,3}, 'v');
  //this->matrix->Set({4,4}, '<');
  //this->matrix->Set({5,5}, '+');
  //this->matrix->Set({6,6}, '-');
  //this->matrix->Set({7,7}, '*');
  //this->matrix->Set({8,8}, '/');
  //
  //this->matrix->Change({5,5}, '#');

  this->run = true;

  this->asciiMode = false;
  this->borderPos = 0.75;
  this->horizontal = true;

  this->showCode = true;
  this->showStack = true;
  this->showLine = true;
  this->showTitle = true;
  this->ideMode = true;

  this->editMode = !false;
}

App::~App() {
  this->run = false;

  this->asciiMode = false;
  this->borderPos = 0;
  this->horizontal = false;

  this->showCode = false;
  this->showStack = false;
  this->showLine = false;
  this->showTitle = false;
  this->ideMode = false;

  this->editMode = false;

  delete this->titleMenuView;
  delete this->codeView;
  delete this->stackView;
  delete this->lineView;
  delete this->termView;

  delete this->editor;
  delete this->runner;
  delete this->matrix;
}

void App::Init(WINDOW* win) {

  //        COLOR_ID,            FG_COLOR,      BG_COLOR
  init_pair(LINE_COLOR_PAIR,     COLOR_BLACK,   COLOR_WHITE );
  init_pair(STACK_COLOR_PAIR,    COLOR_WHITE,   COLOR_BLACK );
  init_pair(TITLE_COLOR_PAIR,    COLOR_BLACK,   COLOR_WHITE );
  init_pair(TERMINAL_COLOR_PAIR, COLOR_WHITE,        -1     );
  init_pair(CODE_COLOR_PAIR,     COLOR_WHITE,        -1     );
  init_pair(CODE_CHANGE_PAIR,    COLOR_CYAN,         -1     );
  init_pair(CODE_CMD_PAIR,       COLOR_YELLOW,       -1     );
  init_pair(CODE_PATH_PAIR,      COLOR_RED,          -1     );
  init_pair(CODE_SPECIAL_PAIR,   COLOR_MAGENTA,      -1     );
  init_pair(CODE_CURSOR_PAIR,    COLOR_WHITE,   COLOR_BLUE  );
  init_pair(CODE_CROSS_PAIR,     COLOR_YELLOW,       -1     );
  init_pair(CODE_RUNNER_PAIR,    COLOR_WHITE,   COLOR_GREEN );
  init_pair(MENU_COLOR_PAIR,     COLOR_WHITE,   COLOR_BLUE  );
  init_pair(MENU_SELECTED_PAIR,  COLOR_BLUE,    COLOR_WHITE );
  init_pair(CODE_NEGATIVE_PAIR,  COLOR_BLACK,        -1     );

  this->win = win;

  this->titleMenuView = new TitleMenuView();
  this->codeView = new CodeView(this->matrix, this->editor, this->runner);
  this->editor->SetCodeView(this->codeView);
  this->stackView = new StackView();
  this->lineView = new LineView();
  this->termView = new TerminalView();
  this->menuView = new MenuView();
}

void App::Update(int input) {
  if (input == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      bool forwardedToMenu = false;
      if (this->menuView->IsOpen())
       if (this->menuView->bounds->Contains({event.x, event.y})) {
        this->menuView->MouseInject(event);
        forwardedToMenu = true;
       } else {
        this->menuView->Close();
      }
      if (!forwardedToMenu) {
        if (this->titleMenuView->bounds->Contains({event.x, event.y})) {
          this->titleMenuView->MouseInject(event);

        } else if (this->codeView->bounds->Contains({event.x, event.y})) {
          this->editor->MouseInject(event);
        }
      }
    }
  } else if (input == KEY_CTRL_SPACE && !this->menuView->IsOpen()) {
    this->menuView->Open();

  } else if (input == KEY_CTRL_SPACE && this->menuView->IsOpen()) {
    this->menuView->Close();

  } else if (input == KEY_ESC && this->menuView->IsOpen()) {
    this->menuView->Close();

  } else if (input == KEY_CTRL_Q) {
    // TODO Save prompt
    this->run = false;

  } else if (input == KEY_CTRL_R) {
    this->horizontal = !this->horizontal;

  } else if (input == KEY_CTRL_4) {
    this->showTitle = !this->showTitle;

  } else if (input == KEY_CTRL_5) {
    this->showCode = !this->showCode;

  } else if (input == KEY_CTRL_6) {
    this->showLine = !this->showLine;

  } else if (input == KEY_CTRL_7) {
    this->showStack = !this->showStack;

  } else if (this->menuView->IsOpen()) {
    this->menuView->Inject(input);

  } else if (this->editMode) {
    this->editor->Inject(input);
  }
}

void App::Draw() {
  getmaxyx(stdscr, this->rows, this->cols);

  // Window is to small
  if (this->cols < 6 || this->rows < 4) {
    clear();
    return;
  }

  // Check BorderPos boundst 0-1
  if (this->borderPos > 1) this->borderPos = 1;
  if (this->borderPos < 0) this->borderPos = 0;

  // Set Title Bounds
  this->titleMenuView->bounds->X(0);
  this->titleMenuView->bounds->Y(0);
  if (this->showTitle) {
    this->titleMenuView->bounds->Height(1);
  } else {
    this->titleMenuView->bounds->Height(0);
  }
  this->titleMenuView->bounds->Width(this->cols);

  // Set Stack Bounds
  this->stackView->bounds->X(this->cols - 3);
  this->stackView->bounds->Y(this->titleMenuView->bounds->Height());
  if (this->showStack) {
    this->stackView->bounds->Width(3);
  } else {
    this->stackView->bounds->Width(0);
  }
  this->stackView->bounds->Height(this->rows - this->titleMenuView->bounds->Height());

  // Set Line Bounds
  if (this->showCode) {
    if (this->horizontal) {
      this->lineView->bounds->X(0);
      this->lineView->bounds->Y(
        this->titleMenuView->bounds->Height() +
        (this->rows - 1 - this->titleMenuView->bounds->Height()) * this->borderPos
      );
      this->lineView->bounds->Height(1);
      this->lineView->bounds->Width(this->cols - this->stackView->bounds->Width());
    } else {
      this->lineView->bounds->Y(this->titleMenuView->bounds->Height());
      this->lineView->bounds->X((this->cols - 1 - this->stackView->bounds->Width()) * this->borderPos);
      this->lineView->bounds->Height(this->rows - this->titleMenuView->bounds->Height());
      this->lineView->bounds->Width(1);
    }
  } else if (this->showLine) {
    this->lineView->bounds->X(0);
    this->lineView->bounds->Y(this->rows - 1);
    this->lineView->bounds->Width(this->cols - this->stackView->bounds->Width());
    this->lineView->bounds->Height(1);
  } else {
    this->lineView->bounds->X(0);
    this->lineView->bounds->Y(this->titleMenuView->bounds->Height());
    this->lineView->bounds->Height(0);
    this->lineView->bounds->Width(0);
  }

  // Set Code Bounds
  this->codeView->bounds->X(0);
  this->codeView->bounds->Y(this->titleMenuView->bounds->Height());
  if (this->showCode) {
    if (this->horizontal) {
      this->codeView->bounds->Height(this->lineView->bounds->Y() - this->titleMenuView->bounds->Height());
      this->codeView->bounds->Width(this->cols - 1 - this->stackView->bounds->Width());
    } else {
      this->codeView->bounds->Height(this->rows - this->titleMenuView->bounds->Height());
      this->codeView->bounds->Width(this->lineView->bounds->X());
    }
  } else {
    this->codeView->bounds->Height(0);
    this->codeView->bounds->Width(0);
  }

  // Set Terminal Bounds
  if ((!(this->showCode)) && this->showLine) {
    this->termView->bounds->X(0);
    this->termView->bounds->Y(this->titleMenuView->bounds->Height());
    this->termView->bounds->Height(this->rows - this->titleMenuView->bounds->Height() - this->lineView->bounds->Height());
    this->termView->bounds->Width(this->cols - this->stackView->bounds->Width());
  } else {
    if (this->horizontal) {
      this->termView->bounds->X(0);
      this->termView->bounds->Y(this->lineView->bounds->Y() + this->lineView->bounds->Height());
      this->termView->bounds->Height(
        this->rows -
        this->lineView->bounds->Height() -
        this->titleMenuView->bounds->Height() -
        this->codeView->bounds->Height()
      );
      this->termView->bounds->Width(this->cols - this->stackView->bounds->Width());
    } else {
      this->termView->bounds->X(this->lineView->bounds->X() + this->lineView->bounds->Width());
      this->termView->bounds->Y(this->titleMenuView->bounds->Height());
      this->termView->bounds->Height(this->rows - this->titleMenuView->bounds->Height());
      this->termView->bounds->Width(
        this->cols -
        this->lineView->bounds->Width() -
        this->stackView->bounds->Width() -
        this->codeView->bounds->Width()
      );
    }
  }

  // Update Views
  if (this->showCode) {
    this->codeView->Show();
    this->codeView->Update();
  } else {
    this->codeView->Hide();
  }
  if (this->showLine || this->showCode) {
    this->lineView->Show();
    this->lineView->Update();
  } else {
    this->lineView->Hide();
  }
  if (this->showTitle) {
    this->titleMenuView->Show();
    this->titleMenuView->Update();
  } else {
    this->titleMenuView->Hide();
  }
  if (this->showStack) {
    this->stackView->Show();
    this->stackView->Update();
  } else {
    this->stackView->Hide();
  }
  this->termView->Update();
  this->menuView->Update();

  // Draw Views
  if (this->showCode) this->codeView->Draw();
  if (this->showLine || this->showCode) this->lineView->Draw();
  if (this->showTitle) this->titleMenuView->Draw();
  if (this->showStack) this->stackView->Draw();
  this->termView->Draw();
  this->menuView->Draw();

  update_panels();
  doupdate();
}

#endif
