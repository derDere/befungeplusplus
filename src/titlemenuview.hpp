#ifndef TITLEMENUVIEW_HPP
#define TITLEMENUVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"

using namespace std;

class TitleMenuView : public View {

  private:
    string title;

  public:
    TitleMenuView();
    ~TitleMenuView();

    void Draw();
    void Update();
};

#endif
