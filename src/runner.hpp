#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "matrix.hpp"
#include "point.hpp"

class Runner : public Point {

  private:
    Point* direction;

  public:
    Runner(int, int);
    Runner();
    ~Runner();
};

#endif
