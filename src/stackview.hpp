#ifndef STACKVIEW_HPP
#define STACKVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"

using namespace std;

class StackView : public View {

  private:
    string code;

  public:
    StackView();
    ~StackView();

    void Draw();
    void Update();
};

#endif
