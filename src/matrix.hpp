#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include <map>

#include "point.hpp"

using namespace std;

class Matrix {

  private:
    map<Point, char, PointCompare>* original;
    map<Point, char, PointCompare>* changes;

  public:
    Matrix();
    ~Matrix();

    char Get(Point);
    void Set(Point, char);
    void Change(Point, char);
    bool Changed(Point);

    void Reset();
    void Import(string);
    string Export();

};

#endif
