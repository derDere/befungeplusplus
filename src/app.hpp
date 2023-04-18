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

using namespace std;

namespace BefungePlusPlus
{
  class App {

    private:
      WINDOW* win;
      int cols, rows;

      TitleMenuView* titleMenuView;
      CodeView* codeView;
      StackView* stackView;
      LineView* lineView;
      TerminalView* termView;

      Matrix* matrix;
      Runner* runner;
      Editor* editor;


    public:
      bool asciiMode;
      float borderPos;
      bool horizontal;

      bool showCode;
      bool showStack;
      bool showLine;
      bool showTitle;
      bool ideMode;

      bool editMode;
      bool editStrMode;

      App();
      ~App();

      void Init(WINDOW*);
      void Draw();
  };
}

#endif
