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
#include "helpview.hpp"

using namespace std;

namespace BefungePlusPlus
{
  class App {

    private:
      WINDOW* win;
      int cols, rows;
      bool run;

      string filepath;

      TitleMenuView* titleMenuView;
      StackView* stackView;
      LineView* lineView;
      TerminalView* termView;
      CodeView* codeView;
      MenuView* menuView;
      HelpView* helpView;

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

      App();
      ~App();

      void Init(WINDOW*);
      void Update(int);
      void Draw();

      bool IsRunning();

      void New();
      void Save();
      void SaveAs();
      void Open();
      void Quit();
  };
}

#endif
