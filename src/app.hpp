#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <ncursesw/ncurses.h>

#include "colors.hpp"
#include "titlemenuview.hpp"
#include "codeview.hpp"
#include "stackview.hpp"
#include "lineview.hpp"
#include "terminalview.hpp"
#include "matrix.hpp"
#include "runner.hpp"
#include "editor.hpp"
#include "menuview.hpp"

using namespace std;

namespace BefungePlusPlus
{
  class App {

    private:
      WINDOW* win;
      int cols, rows;

      TitleMenuView* titleMenuView;
      StackView* stackView;
      LineView* lineView;
      TerminalView* termView;
      CodeView* codeView;
      MenuView* menuView;

      Matrix* matrix;
      Runner* runner;
      Editor* editor;

    public:
      bool run;

      bool asciiMode;
      float borderPos;
      bool horizontal;

      bool showCode;
      bool showStack;
      bool showLine;
      bool showTitle;
      bool ideMode;

      bool editMode;

      App();
      ~App();

      void Init(WINDOW*);
      void Update(int);
      void Draw();
  };
}

#endif
