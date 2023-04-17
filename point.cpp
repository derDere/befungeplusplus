#ifndef POINT_CPP
#define POINT_CPP

#include "point.hpp"

using namespace std;

Point::Point(int x, int y) {
  this->_x = x;
  this->_y = y;
}

Point::Point() : Point(0, 0) {}

Point::~Point() {
  this->_x = 0;
  this->_y = 0;
}

int Point::X() {
  return this->_x;
}

void Point::X(int newX) {
  this->_x = newX;
}

int Point::Y() {
  return this->_y;
}

void Point::Y(int newY) {
  this->_y = newY;
}

void Point::Mv(int xD, int yD) {
  this->_x += xD;
  this->_y += yD;
}

void Point::MvUp() {
  this->Mv(UP);
}

void Point::MvDown() {
  this->Mv(DOWN);
}

void Point::MvLeft() {
  this->Mv(LEFT);
}

void Point::MvRight() {
  this->Mv(RIGHT);
}


#endif
