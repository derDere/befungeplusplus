#ifndef LINEVIEW_HPP
#define LINEVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"

using namespace std;

class LineView : public View {

  private:
    string code;

  public:
    LineView();
    ~LineView();

    void Draw();
    void Update();
};

#endif
