#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.hpp"

using namespace std;

Matrix::Matrix() {
  this->original = new map<Point, char, PointCompare>();
  this->changes = new map<Point, char, PointCompare>();
}

Matrix::~Matrix() {
  this->changes->clear();
  this->original->clear();
  delete this->original;
  delete this->changes;
}

char Matrix::Get(Point key) {
  map<Point, char>::const_iterator i = this->changes->find(key);
  if (i == this->changes->end()) {
    i = this->original->find(key);
    if (i != this->original->end()) {
      return i->second;
    } else {
      return ' ';
    }
  } else {
    return i->second;
  }
}

void Matrix::Set(Point key, char value) {
  if (value == ' ') {
    this->original->erase(key);
  } else {
    (*(this->original))[key] = value;
  }
}

void Matrix::Change(Point key, char value) {
  if (value == ' ') {
    this->changes->erase(key);
  } else {
    (*(this->changes))[key] = value;
  }
}

bool Matrix::Changed(Point key) {
  map<Point, char>::const_iterator i = this->changes->find(key);
  return !(i == this->changes->end());
}

void Matrix::Reset() {
  this->changes->clear();
}

void Matrix::Import(string data) {

}

string Matrix::Export() {

}

#endif
