#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP

#include <string>

using namespace std;

class MenuOption {

  private:
    string display;
    int shortcut;

  public:
    MenuOption(string, int);
    ~MenuOption();

    string Display();
    int Shortcut();

    bool IsShortcut(int);
};

#endif
