#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <string>
#include <vector>

#include "menuoption.hpp"
#include "colors.hpp"
#include "view.hpp"

class MenuView : public View {

  private:
    vector<MenuOption*>* options;
    int selected;
    bool open;

  public:
    MenuView();
    ~MenuView();

    void AddOption(string, int);
    void RemoveOption(int);
    void ClearOptions();
    bool IsOpen();
    void Open();
    void Close();

    void Inject(int);
    void Draw();
    void Update();
};

#endif
