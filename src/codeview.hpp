#ifndef CODEVIEW_HPP
#define CODEVIEW_HPP

#include <string>

#include "colors.hpp"
#include "view.hpp"
#include "matrix.hpp"
#include "editor.hpp"
#include "runner.hpp"

class CodeView : public View {

  private:
    Matrix* matrix;
    Editor* editor;
    Runner* runner;

  public:
    CodeView(Matrix*, Editor*, Runner*);
    ~CodeView();

    void Draw();
    void Update();
};

#endif
