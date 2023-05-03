#ifndef TITLEMENUVIEW_HPP
#define TITLEMENUVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"
#include "menuview.hpp"

using namespace std;

class TitleMenuView : public View {

  private:
    string title;
    MenuView* menuView;
    bool quitRequested;

  public:
    TitleMenuView(MenuView*);
    ~TitleMenuView();

    void SetTitle(string title);

    void MouseInject(MEVENT);
    void Draw();
    void Update();
    bool IsQuitRequested();
};

#endif
