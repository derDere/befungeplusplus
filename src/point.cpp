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

void Point::Set(int x,int y) {
  this->_x = x;
  this->_y = y;
}

void Point::Add(Point* additor) {
  this->_x += additor->_x;
  this->_y += additor->_y;
}

void Point::Sub(Point* additor) {
  this->_x -= additor->_x;
  this->_y -= additor->_y;
}

bool Point::Is(int x, int y) {
  return ((this->_x == x) && (this->_y == y));
}

long Point::Value() const {
  return (((unsigned long)this->_x) << 16) | ((unsigned long)this->_y);
}

bool PointCompare::operator()(const Point& a, const Point& b) const {
  return a.Value() < b.Value();
}

#endif
