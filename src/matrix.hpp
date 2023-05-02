#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include <map>
#include <vector>

#include "point.hpp"
#include "rect.hpp"

#define MATRIX_HISTORY_SIZE 1000

using namespace std;

class Matrix {

  private:
    map<Point, char, PointCompare>* original;
    map<Point, char, PointCompare>* changes;

    struct ChangeStep
    {
      Point key;
      char old_value;
      char new_value;
    };
    vector<ChangeStep>* history;
    vector<ChangeStep>* future;

  public:
    Matrix();
    ~Matrix();

    char Get(Point);
    void Set(Point, char, bool = true);
    void Change(Point, char);
    bool Changed(Point);

    int StartX();
    int StartY();
    int Width();
    int Height();

    void Reset();
    void Import(string, Point* = nullptr);
    string Export(Rect* = nullptr);

    bool Undo(Point&);
    bool Redo(Point&);
};

#endif
