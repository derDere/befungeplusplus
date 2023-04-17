#ifndef CODEVIEW_HPP
#define CODEVIEW_HPP

#include <string>
#include "view.hpp"

class CodeView : public View {

  private:
    string code;

  public:
    CodeView();
    ~CodeView();

    void Draw();
    void Update();
};

#endif
