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
  this->Reset();
  int x = 0;
  int y = 0;
  for (int i = 0; i < data.length(); i++) {
    char c = data[i];
    if (c == '\n') {
      y++;
      x = 0;
    } else {
      this->Set({x,y}, c);
      x++;
    }
  }
}

string Matrix::Export() {
  string data = "";
  for (int y = 0; y < this->Height(); y++) {
    for (int x = 0; x < this->Width(); x++) {
      data += this->Get({x,y});
    }
    data += "\n";
  }
  return data;
}

int Matrix::Width() {
  int width = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int x = i->first.X();
    if (x > width) {
      width = x;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int x = i->first.X();
    if (x > width) {
      width = x;
    }
  }
  return width;
}

int Matrix::Height() {
  int height = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int y = i->first.Y();
    if (y > height) {
      height = y;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int y = i->first.Y();
    if (y > height) {
      height = y;
    }
  }
  return height;
}

#endif
