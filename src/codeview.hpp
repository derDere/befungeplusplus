#ifndef CODEVIEW_HPP
#define CODEVIEW_HPP

#include <string>

class CodeView;

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
    Point* viewPoint;

  public:
    bool showCross;

    CodeView(Matrix*, Editor*, Runner*);
    ~CodeView();

    void Draw();
    void Update();

    int viewX();
    int viewY();
    int viewMarginX();
    int viewMarginY();
    int viewWidth();
    int viewHeight();
};

#endif
