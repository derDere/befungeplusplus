#ifndef RUNNER_CPP
#define RUNNER_CPP

#include "runner.hpp"

using namespace std;

Runner::Runner(int x, int y) : Point(x, y) {
  this->direction = new Point(1, 0);
}

Runner::Runner() : Runner(0, 0) { }

Runner::~Runner() {
  delete this->direction;
}

#endif
