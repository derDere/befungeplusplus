#ifndef TERMINALVIEW_HPP
#define TERMINALVIEW_HPP

#include <string>
#include "view.hpp"

using namespace std;

class TerminalView : public View {

  private:
    string code;

  public:
    TerminalView();
    ~TerminalView();

    void Draw();
    void Update();
};

#endif
