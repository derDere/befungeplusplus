#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <ncursesw/ncurses.h>
#include "codeview.hpp"
#include "terminalview.hpp"

using namespace std;

namespace BefungePlusPlus
{
  class App {

    private:
      WINDOW* win;
      int cols, rows;
      CodeView* codeView;
      TerminalView* termView;

    public:
      float borderPos;
      bool horizontal;
      bool showCode;
      bool editMode;
      bool editStrMode;
      bool asciiMode;

      App();
      ~App();

      void Init(WINDOW*);
      void Draw();
  };
}

#endif
