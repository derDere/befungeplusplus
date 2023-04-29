#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.hpp"

using namespace std;

Matrix::Matrix() {
  this->original = new map<Point, char, PointCompare>();
  this->changes = new map<Point, char, PointCompare>();
  this->history = new vector<ChangeStep>();
  this->future = new vector<ChangeStep>();
}

Matrix::~Matrix() {
  this->changes->clear();
  this->original->clear();
  this->history->clear();
  this->future->clear();
  delete this->original;
  delete this->changes;
  delete this->history;
  delete this->future;
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

void Matrix::Set(Point key, char value, bool changeHistory) {
  char old_value = this->Get(key);
  if (old_value != value) {
    if (value == ' ') {
      this->original->erase(key);
    } else {
      (*(this->original))[key] = value;
    }
    if (changeHistory) {
      this->history->push_back({key, old_value, value});
      this->future->clear();
      while (this->history->size() > MATRIX_HISTORY_SIZE) {
        this->history->erase(this->history->begin());
      }
    }
  }
}

bool Matrix::Undo(Point& key) {
  if (this->history->size() > 0) {
    ChangeStep change = this->history->back();
    this->history->pop_back();
    this->future->push_back(change);
    this->Set(change.key, change.old_value, false);
    key = change.key;
    return true;
  }
  return false;
}

bool Matrix::Redo(Point& key) {
  if (this->future->size() > 0) {
    ChangeStep change = this->future->back();
    this->future->pop_back();
    this->history->push_back(change);
    this->Set(change.key, change.new_value, false);
    key = change.key;
    return true;
  }
  return false;
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

string Matrix::Export(Rect* rect) {
  string data = "";
  for (int y = this->StartY(); y < this->Height(); y++) {
    for (int x = this->StartX(); x < this->Width(); x++) {
      data += this->Get({x,y});
    }
    data += "\n";
  }
  return data;
}

int Matrix::StartX() {
  int minX = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int x = i->first.X();
    if (x < minX) {
      minX = x;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int x = i->first.X();
    if (x < minX) {
      minX = x;
    }
  }
  return minX;
}

int Matrix::StartY() {
  int minY = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int y = i->first.Y();
    if (y < minY) {
      minY = y;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int y = i->first.Y();
    if (y < minY) {
      minY = y;
    }
  }
  return minY;
}

int Matrix::Width() {
  int minX = 0;
  int maxX = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int x = i->first.X();
    if (x < minX) {
      minX = x;
    }
    if (x > maxX) {
      maxX = x;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int x = i->first.X();
    if (x < minX) {
      minX = x;
    }
    if (x > maxX) {
      maxX = x;
    }
  }
  return maxX - minX;
}

int Matrix::Height() {
  int minY = 0;
  int maxY = 0;
  for (map<Point, char>::iterator i = this->original->begin(); i != this->original->end(); i++) {
    int y = i->first.Y();
    if (y < minY) {
      minY = y;
    }
    if (y > maxY) {
      maxY = y;
    }
  }
  for (map<Point, char>::iterator i = this->changes->begin(); i != this->changes->end(); i++) {
    int y = i->first.Y();
    if (y < minY) {
      minY = y;
    }
    if (y > maxY) {
      maxY = y;
    }
  }
  return maxY - minY;
}

#endif
