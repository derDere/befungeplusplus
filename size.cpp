#ifndef SIZE_CPP
#define SIZE_CPP

#include "size.hpp"

using namespace std;

Size::Size(int width, int height) {
  this->_width = width;
  this->_height = height;
}

Size::Size() : Size::Size(0, 0) { }

Size::~Size() {
  this->_width = 0;
  this->_height = 0;
}

int Size::Width() {
  return this->_width;
}

void Size::Width(int newWidth) {
  this->_width = newWidth;
}

int Size::Height() {
  return this->_height;
}

void Size::Height(int newHeight) {
  this->_height = newHeight;
}

#endif
