#ifndef EDITOR_HPP
#define EDITOR_HPP

class Editor;

#include "matrix.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "codeview.hpp"

using namespace std;

class Editor {
  private:
    Matrix* matrix;
    CodeView* codeView;
    bool strMode;

  public:
    Point* position;
    Point* direction;
    Size* selection;

    Editor(Matrix*);
    ~Editor();

    void Inject(int);
    void MouseInject(MEVENT);
    void SetCodeView(CodeView*);
};

#endif
