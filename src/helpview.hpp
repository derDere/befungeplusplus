#ifndef HELPVIEW_HPP
#define HELPVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"

using namespace std;

class HelpView : public View {

  private:
    string code;
    bool visible;

  public:
    HelpView();
    ~HelpView();

    void Open();
    void Close();
    bool IsVisible();

    void Draw();
    void Update();
};

#endif
